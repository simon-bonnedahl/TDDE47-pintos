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
pid_t exec(const char *cmd_line);
int wait(pid_t pid);
struct file_descriptor * get_file_descriptor (int fd);
bool valid_address(void *vaddr);
bool valid_string(const char *str);
bool valid_buffer(void *buffer, unsigned size);
bool valid_fd(int fd);
void kill();
void seek(int fd, unsigned position);
unsigned tell(int fd);
int filesize(int fd);
bool remove(const char *file_name);




//declare a variable that tracks the amount of open files
//#define int OPEN_FILES = 2;
#define STDIN_FILENO 0;
#define STDOUT_FILENO 1;