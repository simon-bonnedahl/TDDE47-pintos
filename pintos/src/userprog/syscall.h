#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H
#include "lib/user/syscall.h"


void syscall_init(void);

#endif /* userprog/syscall.h */

void halt(void);
void exit(int status);
bool create(const char *file, unsigned initial_size);
int open(const char *file);
int read(int fd, void *buffer, unsigned size);
int write(int fd, const void *buffer, unsigned size);
void close(int fd);
struct fd_elem * get_file (int fd);

//declare a variable that tracks the amount of open files
//#define int OPEN_FILES = 2;
#define STDIN_FILENO 0;
#define STDOUT_FILENO 1;