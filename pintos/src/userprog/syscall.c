#include "threads/thread.h"
#include <debug.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "syscall.h"
static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{

  //get the system call number
  int syscall_num = *(f->esp);

  switch(syscall_num){

    case SYS_HALT:
      halt();
      break;
    case SYS_WRITE:
      printf ("system call!\n");
      thread_exit ();
      break;
    case SYS_EXIT:
      printf ("system call!\n");
      thread_exit ();
      break;
    case SYS_CREATE:
      // 2 arguments
      int fileDescriptor = *(f->esp + 4);
      int fileSize = *(f->esp + 8);
      //validate the arguments  
      ASSERT(fileDescriptor != NULL);
      ASSERT(fileSize != NULL);
      f->eax = create(fileDescriptor, fileSize);
      break;
    case SYS_OPEN:
      // 1 argument
      int fileName = *(f->esp + 4);
      //validate the arguments
      ASSERT(fileName != NULL);
      int fileDescriptor = open(fileName);
      break;
    case SYS_CLOSE:
      // 1 argument
      int fileDescriptor = *(f->esp + 4);
      //validate the arguments
      ASSERT(fileDescriptor != NULL);
      f->eax = close(fileDescriptor);
      break;

    case SYS_READ:
      // 3 arguments
      int fileDescriptor = *(f->esp + 4);
      int buffer = *(f->esp + 8);
      int fileSize = *(f->esp + 12);
      //validate the arguments
      ASSERT(fileDescriptor != NULL);
      ASSERT(buffer != NULL);
      ASSERT(fileSize != NULL);
      f->eax = read(fileDescriptor, buffer, fileSize);
      break;
  }
  printf ("system call!\n");
  thread_exit ();
}

//define all the system calls here from the header

void halt(void){
  shutdown_power_off();
}

void exit(int status){
  thread_current()->exit_status = status;
  printf("%s: exit(%d)", thread_current()->name, status);
  }


bool create(const char *file, unsigned initial_size){
  //create a file
  return filesys_create(file, initial_size);

}

int open(const char *file){

  //open the file
  struct file = filesys_open(file);
  if(file == NULL){
    return -1;
  }
  return file->fd;

}

void close(int fd){
  //close the file

 file_close(fd);
}

int read(int fd, void *buffer, unsigned size){
  if(fd == STDIN_FILENO){
    int len = 0;
    while(len < size){
      char c = input_getc();
      if(c == '\0'){
        break;
      }
      buffer[len] = c;
      len++;
    }
    return len;
  }else{
    struct file_desc *fd = get_file_desc(fd);
    file_read(fd, buffer, size);
  }
}

void write(int fd, const void *buffer, unsigned size){
  if(fd == 1){
    putbuf(buffer, size);
  }
}

struct file_desc * get_file_desc(int fd){
  struct thread *t = thread_current();
  struct list_elem *e;
  for(e = list_begin(&t->file_desc_list); e != list_end(&t->file_desc_list); e = list_next(e)){
    struct file_desc *fd = list_entry(e, struct file_desc, elem);
    if(fd->fd == fd){
      return fd;
    }
  }
  return NULL;
}

