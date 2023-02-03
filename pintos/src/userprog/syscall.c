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

/*pintos --qemu -p ../../examples/lab1test2 -a test2 -- -q*/
/*pintos --qemu -p ../../examples/lab1test2 -a test2 -- -q run test2*/
/*pintos -- rm test2*/

static void syscall_handler(struct intr_frame *);


struct file_descriptor
{
  int value;
  struct file *file;
  struct list_elem elem;
};

void syscall_init(void)
{
  intr_register_int(0x30, 3, INTR_ON, syscall_handler, "syscall");
  

}

static void
syscall_handler(struct intr_frame *f UNUSED)
{
  
  int *stack_pointer = f->esp;
  int syscall = *stack_pointer;
  if (!valid(stack_pointer))
    kill();

  // hex_dump(stack_pointer, stack_pointer, 128, true);

  int status;
  int fileDescriptor;
  unsigned fileSize;
  char *fileName;
  const void *buffer;

  printf("syscall: %d \n", syscall);
  switch (syscall)
  {

  case SYS_HALT:
    halt();
    break;

  case SYS_EXIT:
    status = *(int *)(f->esp + 4);
    exit(status);
    break;

  case SYS_WRITE:
    // 3 arguments
    fileDescriptor = *(int *)(f->esp + 4);
    buffer = *(void **)(f->esp + 8);
    fileSize = *(unsigned *)(f->esp + 12);

    // hex_dump(f->esp+8, f->esp+8, 64, true);
    f->eax = write(fileDescriptor, buffer, fileSize);

    break;
  case SYS_CREATE:
    // 2 arguments
    fileName = *(char **)(f->esp + 4);
    fileSize = *(unsigned *)(f->esp + 8);
    f->eax = create(fileName, fileSize);

    break;
  case SYS_OPEN:
    // 1 argument
    fileName = *(char **)(f->esp + 4);
    f->eax = open(fileName);
    break;
  case SYS_CLOSE:
    // 1 argument
    fileDescriptor = *(int *)(f->esp + 4);
    close(fileDescriptor);
    break;

  case SYS_READ:

    // 3 arguments
    fileDescriptor = *(int *)(f->esp + 4);
    buffer = *(void **)(f->esp + 8);
    fileSize = *(unsigned *)(f->esp + 12);

    f->eax = read(fileDescriptor, buffer, fileSize);
    break;
  case SYS_EXEC:
    // 1 argument
    fileName = *(char **)(f->esp + 4);
    f->eax = exec(fileName);
    break;

  default:
    printf("Unknown system call!");
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

  struct list_elem *e;
  struct file_descriptor *file_descriptor;
  struct thread *t = thread_current();
  for (e = list_begin(&t->fd_list); e != list_end(&t->fd_list); e = list_next(e))
  {
    file_descriptor = list_entry(e, struct file_descriptor, elem);
    file_close(file_descriptor->file);
    list_remove(&file_descriptor->elem);
    free(file_descriptor);
  }

  printf("%s: exit(%d)", thread_current()->name, status);
  thread_current()->status = status;
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

bool valid(void *vaddr)
{
  return (is_user_vaddr(vaddr) && pagedir_get_page(thread_current()->pagedir, vaddr) != NULL);
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
  //spawn a new child process
  
  return process_execute(cmd_line);
}