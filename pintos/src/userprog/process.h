#ifndef USERPROG_PROCESS_H
#define USERPROG_PROCESS_H

#include "threads/thread.h"

tid_t process_execute (const char *file_name);
int process_wait (tid_t);
void process_exit (void);
void process_activate (void);




struct parent_child * get_relation(tid_t tid, struct thread *t);

struct exec_info {
  char *file_name;
  struct semaphore sema;
  struct parent_child relation;
};


#endif /* userprog/process.h */
