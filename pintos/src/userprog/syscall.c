#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler(struct intr_frame *);

void syscall_init(void)
{
  intr_register_int(0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler(struct intr_frame *f UNUSED)
{
  // validate argument

  // get system call number
  int syscall_num = *(int *)f->esp;

  switch (syscall_num)
  {
  case SYS_WRITE:
    int fileDescriptor = *(int *)(f->esp + 4);
    const void *buffer = *(const void **)(f->esp + 8);
    unsigned size = *(unsigned *)(f->esp + 12);

    if (fd < 0 || buffer == NULL || size < 0)
    {
      thread_exit();
    }
    void arguments[3] = {fileDescriptor, buffer, size};

    thread_create("write", PRI_DEFAULT, write, arguments);

    break;
  case SYS_READ:
    break;
  case SYS_HALT:
    break;
  case SYS_EXIT:
    break;
  case SYS_EXEC:
    break;

  default:
    thread_exit();
    break;
  }
  printf("system call!\n");
}
