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


/*pintos --qemu -p ../../examples/lab1test2 -a test2 -- -q*/
/*pintos --qemu -p ../../examples/lab1test2 -a test2 -- -q run test2*/
/*pintos --qemu -- rm test2*/
#include "userprog/pagedir.h"

static void syscall_handler (struct intr_frame *);
int OPEN_FILES = 2;

struct fd_elem{
  int fd;
  struct file * file;
  struct list_elem elem;
};  

void syscall_init(void)
{
  intr_register_int(0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler(struct intr_frame *f UNUSED)
{

  int * stack_pointer = f->esp;
  int syscall = *stack_pointer;

  hex_dump(stack_pointer, stack_pointer, 128, true);

  int status;
  int fileDescriptor;
  int fileSize;
  char* fileName;
  char* buffer;
  


  switch (syscall) {

    case SYS_HALT:
      halt();
      break;
    
    case SYS_EXIT:
      status = *(int*)(f->esp + 4);
      exit(status);
      break;   
    case SYS_WRITE:
      // 3 arguments

      //hex_dump(f->esp+8, f->esp+8, 64, true);
      f->eax = write(*(int*)(f->esp +4), (f->esp +8), *(int*)(f->esp +12));

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
  printf("HEJ!");
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
  if(fd == 0){
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
  //validate arguments
  if(buffer == NULL || !is_user_vaddr(buffer)){
    exit(-1);
  }
  if(fd == 0){
    exit(-1);
  }

 
  if(fd == 1){

    putbuf(buffer, size);
    return size;
  }
  
  struct fd_elem * fd_elem = get_file(fd);
  if(fd_elem == NULL){
    return -1;
  } 

  

  return file_write(fd_elem->file, buffer, size);

  

}

struct fd_elem * get_file (int fd) {

  struct thread *t = thread_current();
  struct list_elem *e;
  
  for(e = list_begin(&t->open_files); e != list_end(&t->open_files); e = list_next(e)){
    struct fd_elem *fd_elem = list_entry(e, struct fd_elem, elem);

    if(fd_elem->fd == fd){

      return fd_elem;
    }
  }
  return NULL;

} 
