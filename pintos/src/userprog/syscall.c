#include "threads/thread.h"
#include <debug.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "syscall.h"
#include "syscall-nr.h"
#include "threads/interrupt.h"
#include "threads/vaddr.h"
#include "threads/synch.h"
#include "threads/malloc.h"
#include "devices/input.h"
#include "userprog/process.h"
#include "userprog/pagedir.h"


void syscall_init(void)
{
  intr_register_int(0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler(struct intr_frame *f UNUSED)
{

  //get the system call number
  int syscall_num = *(int*)(f->esp);
  int status;
  int fileDescriptor;
  int fileSize;
  char* fileName;
  char* buffer;


  switch (syscall_num) {

    case SYS_HALT:
      halt();
      break;
    
    case SYS_EXIT:
      status = *(int*)(f->esp + 4);
      exit(status);
      break;   
    case SYS_WRITE:

      printf ("system call!\n");
      thread_exit ();
      break;
    case SYS_CREATE:
      // 2 arguments
      fileDescriptor = *(int*)(f->esp + 4);
      fileSize = *(int*)(f->esp + 8);
      ASSERT(fileDescriptor != NULL);
      ASSERT(fileSize != NULL);
      f->eax = create(fileDescriptor, fileSize);
      break;
    case SYS_OPEN:
      // 1 argument
      fileName = *(int*)(f->esp + 4);
      ASSERT(fileName != NULL);
      fileDescriptor = open(fileName);
      break;
    case SYS_CLOSE:
      // 1 argument
      fileDescriptor = *(int*)(f->esp + 4);
      ASSERT(fileDescriptor != NULL);
      close(fileDescriptor);

      break;

    case SYS_READ:
      // 3 arguments
      fileDescriptor = *(int*)(f->esp + 4);
      buffer = *(char*)(f->esp + 8);
      fileSize = *(int*)(f->esp + 12);
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

    struct file* open_files[128];         //Lab 1

void halt(void){
  power_off();
}

void exit(int status){
  thread_current()->status = status;
  //close all the files in thread_current()->open_files
  struct file* open_files = thread_current()->open_files;
  for(int i = 2; i < OPEN_FILES; i++){
    close(i);
  }

  printf("%s: exit(%d)", thread_current()->name, status);
  thread_exit();

}

bool create(const char *file, unsigned initial_size){
  //create a file
  return filesys_create(file, initial_size);

}

int open(const char* filename){

  //open the file
  struct file* open_file = filesys_open(filename);
  open_files[OPEN_FILES] = open_file;
  if(open_file == NULL){
    return -1;
  }
  return OPEN_FILES++;

}

void close(int fd){


 file_close(thread_current()->open_files[fd]);
  thread_current()->open_files[fd]= NULL;
  OPEN_FILES--;
  
 
  //close the file
  
  

}

int read(int fd, void *buffer, unsigned size){
  if(fd == STDIN_FILENO){
    int len = 0;
    while(len < size){
      char c = input_getc();
      if(c == '\0'){
        break;
      }
      //buffer[len] = c;
      len++;
    }
    return len;
  }else{
    //struct file_desc *fd = get_file_desc(fd);
    //file_read(fd, buffer, size);
  }
}

int write(int fd, const void *buffer, unsigned size){
  if(fd == 1){
    putbuf(buffer, size);
  }
  return 0;
}
/*struct file_desc * get_file_desc(int fd){
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

*/
