#ifndef USERPROG_PROCESS_H
#define USERPROG_PROCESS_H

#include "threads/thread.h"

tid_t process_execute (const char *file_name);
int process_wait (tid_t);
void process_exit (void);
void process_activate (void);


/*Lab 3*/
struct child {
  tid_t tid;
  int exit_status;
  bool exited;
  struct list_elem elem;
};

struct child * get_child(tid_t tid, struct thread *t);


#endif /* userprog/process.h */
