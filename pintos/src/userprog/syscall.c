#include "threads/thread.h"
#include <debug.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <list.h>

#include "syscall.h"
#include "syscall-nr.h"
#include "threads/interrupt.h"
#include "threads/vaddr.h"
#include "threads/synch.h"
#include "threads/malloc.h"
#include "devices/input.h"
#include "userprog/process.h"
#include "userprog/pagedir.h"

static void syscall_handler(struct intr_frame *);

void syscall_init(void)
{
  intr_register_int(0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler(struct intr_frame *f UNUSED)
{
  if (!valid_address(f->esp))
    kill();
  int *stack_pointer = f->esp;
  int syscall = *stack_pointer;

  // hex_dump(stack_pointer, stack_pointer, 128, true);

  int status;
  int fileDescriptor;
  unsigned fileSize;
  char *fileName;
  char *command_line;
  const void *buffer;
  pid_t pid;

  // printf("syscall: %d \n", syscall);
  switch (syscall)
  {

  case SYS_HALT:
    halt();
    break;

  case SYS_EXIT:
  if(!valid_address(f->esp + 4))kill();
    status = *(int *)(f->esp + 4);
    exit(status);
    break;

  case SYS_WRITE:
    // 3 arguments
    if(!valid_address(f->esp + 4))kill();
    if(!valid_address(f->esp + 8))kill();
    if(!valid_address(f->esp + 12))kill();
    fileDescriptor = *(int *)(f->esp + 4);
    buffer = *(void **)(f->esp + 8);
    fileSize = *(unsigned *)(f->esp + 12);
    if(!valid_buffer(buffer, fileSize))kill();
    // hex_dump(f->esp+8, f->esp+8, 64, true);
    f->eax = write(fileDescriptor, buffer, fileSize);

    break;
  case SYS_CREATE:
    // 2 arguments
    if(!valid_address(f->esp + 4))kill();
    if(!valid_address(f->esp + 8))kill();
    fileName = *(char **)(f->esp + 4);
    fileSize = *(unsigned *)(f->esp + 8);
    if(!valid_string(fileName))kill();
    f->eax = create(fileName, fileSize);

    break;
  case SYS_OPEN:
    // 1 argument
    if(!valid_address(f->esp + 4))kill();
    fileName = *(char **)(f->esp + 4);
    if(!valid_string(fileName))kill();
    f->eax = open(fileName);
    break;
  case SYS_CLOSE:
    // 1 argument
    if(!valid_address(f->esp + 4))kill();
    fileDescriptor = *(int *)(f->esp + 4);
    close(fileDescriptor);
    break;

  case SYS_READ:
    if(!valid_address(f->esp + 4))kill();
    if(!valid_address(f->esp + 8))kill();
    if(!valid_address(f->esp + 12))kill();
    // 3 arguments
    fileDescriptor = *(int *)(f->esp + 4);
    buffer = *(void **)(f->esp + 8);
    fileSize = *(unsigned *)(f->esp + 12);
    if(!valid_buffer(buffer, fileSize))kill();
    f->eax = read(fileDescriptor, buffer, fileSize);
    break;
  case SYS_EXEC:
    // 1 argument
    if(!valid_address(f->esp + 4))kill();
    command_line = *(char **)(f->esp + 4);
    if(!valid_string(command_line))kill();
    f->eax = exec(command_line);
    break;
  case SYS_WAIT:
    // 1 argument
    if(!valid_address(f->esp + 4))kill();
    pid = *(int *)(f->esp + 4);
    f->eax = wait(pid);
    break;

  default:
    //printf("Unknown system call!");
    kill();
    break;
  }
}

void halt(void)
{
  power_off();
}

void exit(int status)
{
  thread_current()->parent_relation->exit_status = status;

  printf("%s: exit(%d)\n", thread_current()->name, status);

  thread_exit();
}

bool create(const char *filename, unsigned initial_size)
{

  if (filename == NULL || !is_user_vaddr(filename))
  {
    kill();
  }

  return filesys_create(filename, initial_size);
}

int open(const char *filename)
{

  struct file *open_file = filesys_open(filename);
  if (open_file == NULL)
  {
    return -1;
  }
  struct thread *t = thread_current();
  struct file_descriptor *file_descriptor = malloc(sizeof(struct file_descriptor));
  file_descriptor->value = t->fd_count;
  t->fd_count++;
  file_descriptor->file = open_file;
  list_push_back(&t->fd_list, &file_descriptor->elem);
  return file_descriptor->value;
}

void close(int fd)
{

  if (fd == 0 || fd == 1)
  {
    kill();
  }
  struct file_descriptor *file_descriptor = get_file_descriptor(fd);
  if (file_descriptor == NULL)
  {
    kill();
  }

  file_close(file_descriptor->file);
  list_remove(&file_descriptor->elem);
  // free(file_descriptor); Behövs detta?
}

int read(int fd, void *buffer, unsigned size)
{

  if (fd == 0)
  {
    int len = 0;
    while (len < size)
    {
      char c = input_getc();
      if (c == '\0')
      {
        break;
      }
      len++;
    }
    return len;
  }

  struct file_descriptor *file_descriptor = get_file_descriptor(fd);
  if (file_descriptor == NULL)
    return -1;
  return file_read(file_descriptor->file, buffer, size);
}

int write(int fd, const void *buffer, unsigned size)
{
  // validate arguments
  if (buffer == NULL || !is_user_vaddr(buffer))
  {
    kill();
  }
  if (fd == 0)
  {
    kill();
  }

  if (fd == 1)
  {

    putbuf(buffer, size);
    return size;
  }

  struct file_descriptor *file_descriptor = get_file_descriptor(fd);

  if (file_descriptor == NULL)
  {
    return -1;
  }

  return file_write(file_descriptor->file, buffer, size);
}

struct file_descriptor *get_file_descriptor(int fd)
{
  struct thread *t = thread_current();
  struct list_elem *e;
  for (e = list_begin(&t->fd_list); e != list_end(&t->fd_list); e = list_next(e))
  {
    struct file_descriptor *file_descriptor = list_entry(e, struct file_descriptor, elem);

    if (file_descriptor->value == fd)
    {

      return file_descriptor;
    }
  }
  // printf("file descriptor not found");
  return NULL;
}

bool valid_address(void *vaddr)
{
  return (is_user_vaddr(vaddr) && pagedir_get_page(thread_current()->pagedir, vaddr) != NULL);
}

bool valid_buffer(void *buffer, unsigned size)
{
  unsigned i;
  for (i = 0; i < size; i++)
  {
    if (!valid_address(buffer))
    {
      return false;
    }
  }
  return true;
}

bool valid_string(const char *str)
{
  if (str == NULL)kill();
  if(!valid_address(str))kill();
  
  while (*(str++) != '\0') {    
    if(!valid_address(str))kill();
  }
}


  


void kill()
{
  exit(-1);
}

pid_t exec(const char *cmd_line)
{
  if (cmd_line == NULL || !is_user_vaddr(cmd_line))
  {
    kill();
  }
  // spawn a new child process

  return process_execute(cmd_line);
}

int wait(pid_t pid)
{
  return process_wait(pid);
}
