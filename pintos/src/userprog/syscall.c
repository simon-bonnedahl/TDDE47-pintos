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

/*pintos --qemu -p ../../examples/lab1test2 -a test2 -- -q*/
/*pintos --qemu -p ../../examples/lab1test2 -a test2 -- -q run test2*/
/*pintos -- rm test2*/


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
  list_init(&thread_current()->open_files);
}

static void
syscall_handler(struct intr_frame *f UNUSED)
{

  int * stack_pointer = f->esp;
  int syscall = *stack_pointer;
  if(!valid (stack_pointer))
    kill();


  int status;
  int fileDescriptor;
  unsigned fileSize;
  char* fileName;
  const void* buffer;
  


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
      fileDescriptor = *(int*)(f->esp + 4);
      buffer = *(void**)(f->esp + 8);
      fileSize = *(unsigned*)(f->esp + 12);

      //hex_dump(f->esp+8, f->esp+8, 64, true);
      f->eax = write(fileDescriptor, buffer, fileSize);

      break;
    case SYS_CREATE:
      // 2 arguments
      fileName = *(char**)(f->esp + 4);
      fileSize = *(unsigned*)(f->esp + 8);
      f->eax = create(fileName, fileSize);

      break;
    case SYS_OPEN:
      // 1 argument
      fileName = *(char**)(f->esp + 4);
      f->eax = open(fileName);
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
      buffer = *(void**)(f->esp + 8);
      fileSize = *(unsigned*)(f->esp + 12);

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

bool create(const char* filename, unsigned initial_size){

  if(filename == NULL || !is_user_vaddr(filename)){
    kill();
  }

  return filesys_create(filename, initial_size);
  
}

int open(const char* filename){

  //open the file

  struct file* open_file = filesys_open(filename);
    if(open_file == NULL){
    return -1;
  }
  struct fd_elem *fd_elem = malloc(sizeof(struct fd_elem));
  int fd = OPEN_FILES;
  fd_elem->fd = fd;
  fd_elem->file = open_file;
  list_push_back(&thread_current()->open_files, &fd_elem->elem);
  OPEN_FILES++;
  return fd;
 /* struct fd_elem *fd_elem = malloc(sizeof(struct fd_elem));
  fd_elem->fd = OPEN_FILES;
  fd_elem->file = open_file;
  //list_push_back(student_list, &new_student->elem);
  list_push_back(&thread_current()->open_files, &fd_elem->elem);
  return OPEN_FILES++;*/

}

void close(int fd){

  //validate arguments
  if(fd == 0  || fd == 1){
    exit(-1);
  }

  struct fd_elem* fd_elem = get_fd_elem(fd);
  if(fd_elem == NULL){
    exit(-1);
  }

  file_close(fd_elem->file);
  list_remove(&fd_elem->elem);
  free(fd_elem);
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
  }
  if(open_files[fd] == NULL) return -1;
  return file_read(fd, buffer, size);

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
  
  struct fd_elem * fd_elem = get_fd_elem(fd);
  if(fd_elem == NULL){
    return -1;
  } 

  

  return file_write(fd_elem->file, buffer, size);

  

}

struct fd_elem * get_fd_elem (int fd) {

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

bool valid(void * vaddr)
{
  return (is_user_vaddr(vaddr) && 
    pagedir_get_page(thread_current()->pagedir,vaddr)!=NULL);
}

/* Exits the process with -1 status */
void kill () 
{
  exit(-1);
  
}