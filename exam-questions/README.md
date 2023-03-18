# 2022-03-26:

### Which of the following properties should be ensured according to the critical section problem as defined in the course book?

- A) Mutual exclusion ✅
- B) Lock-freedom
- C) Progress ✅
- D) Availability

### Which of the following statements are true about the PCB?

- A) It contains the process stack and heap
- B) It contains the program counter information ✅
- C) It includes information about the process threads
- D) PCB is short for ’Processor Control Block’ ✅

### A hypervisor is used in virtualization solutions to allow multiple operating systems to run on the same physical hardware. The hypervisor can let the OSs take care of some things on their own, but must have at least some support for certain concepts. Which of the following must be supported by the hypervisor?

- A) File table for files opened by guest OSs
- B) Special instructions (i.e., that require the CPU to be in protected mode) ✅
- C) User management for the guest OSs
- D) Memory management ✅

### Which are NOT the responsibilities of the OS?

A) Decide which process to run
B) Managing the memory for all processes
C) Preventing deadlocks ✅
D) Managing the CPU

### Which of the following mechanisms are intended to speed-up the memory access time?

A) Relocation
B) Translation Look-aside Buffer (TLB) ✅
C) CPU Cache ✅
D) Segmentation

### Which of the following are the weaknesses of the Banker’s algorithm?

A) Assumes a fixed number of resources ✅
B) Assumes that processes state maximum needs in advance ✅
C) Assumes a variable population of processes
D) Assumes that a process will terminate ✅

### Which of the following statements are true?

A) Process termination can help with recovery from deadlock ✅
B) A deadlock detection algorithm is called for each resource request
C) A wait-for graph is a variant of the resource-allocation graph ✅
D) Resource preemption avoids deadlocks

### Consider the program below. How many times will it output the letter “A”?

```
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void main() {
setbuf(stdout, NULL); //disable buffering
printf("A");
pid_t pid1 = fork();
if (pid1 == 0) {
pid_t pid2 = fork();
if (pid2 == 0) {
printf("A");
}
}
printf("A");
}
```

A) 3
B) 5 ✅
C) 6
D) 8

Which of the following methods are reasonable to use when passing a string parameter to a system call?

A) Send the string in a file
B) Put the string as a null-terminated array on the stack
C) Allocate memory on the heap for the string and pass the memory address in a
register
D) Put the string in a register

Consider the following pseudocode implementation of the spinlock-free semaphore
wait operation taken from the lecture slides. An error has been introduced in one of
the lines, which one?

void wait ( semaphore \*S ) {
S->value--;
if (S->value == 0) {
add this process to S->wqueue;
block(); // I release the lock on the critical
} // section for S and release the CPU
}

A) 2
B) 3
C) 4
D) 5

—————————————————————————————————————————

—————————————————————————————————————————
2022-06-08:
—————————————————————————————————————————

Which of the following virtualization configurations are possible when using paravirtualization:

A) Host running Ubuntu Linux on a x86-64 machine, Guest running Windows 10 for x86-64
B) Host running Ubuntu Linux on a x86-64 machine, Guest running Linux for ARM
C) Host running Windows 10 on a x86-64 machine, Guest running Ubuntu Linux for x86-64
D) Host running Ubuntu Linux on an IA-32 machine, Guest running Ubuntu Linux for x86-64

Which of the following statements are true about the PCB?

A) PCB is short for ’Processor Control Block’
B) It contains the program counter information
C) It contains the process stack and heap
D) It contains the translation lookaside buffer (TLB)

Which of the following statements about Banker's algorithm are true?

A) It is a deadlock-preventing algorithm.
B) It is a deadlock-avoiding algorithm.
C) It is a deadlock detection algorithm.
D) It can be used when there are multiple instances of a resource.

Consider the program below. How many times will it output the letter “A”?
#include <studio.h>
#include <sys/types.h>
#include <unistd.h>
int main() {
setbuf(stdout, NULL(; //disable buffering
pid_t pid1 = fork();
printf(“A”);
if (pid1 == 0) {
printf(“A”);
}
printf(“A”);
}

3
5
6
8

Which of the following are possible states for a system process:

A) Waiting
B) Ready
C) Forking
D) Controlling

Which of the following properties are true for semaphores?

A) The wait signal operation is atomic
B) They guarantee freedom from deadlock
C) They can be used to solve the critical section problem
D) They can only be implemented on a system with special hardware

Which of the following statements are true?

A deadlock detection algorithm is called for each resource request
Deadlocks are only affecting threads
A resource-allocation graph can be used to detect deadlocks
No deadlock is possible if any of the Coffman conditions are false

Which of the following operations require a system call to be performed when called from a user program?

Reading from memory allocated on the heap
Allocating new memory on the heap
Reading from a file on disk
Making a regular function call

Which of the following items are found in a POSIX inode for a regular file?

A) File size
B) Pointer to the directory that the file is located in
C) Pointers to blocks on disk where the file is stored
D) The file position indicator (as set by an fseek command)

Which of the following statements are true?

A) A process in a modern operating system has its own protected memory
B) Different threads belonging to the same process share memory with each other.
C) A thread is only run when there is no process that wants to use the CPU.
D) Threads are guaranteed to be deadlock-free

—————————————————————————————————————————

—————————————————————————————————————————
2022-08-22:
—————————————————————————————————————————

Which of these algorithms may exhibit the Belady’s anomaly?

A) LRU replacement
B) Second-chance replacement (based on FIFO)
C) FIFO replacement
D) Optimal replacement

Which of the following mechanisms will prevent deadlocks?

A) Only use safe resources
B) Always acquire resources according to a globally defined order
C) Ensure that ∀j : Rj ≥ P i D(i, j), where Rj is the number of instances of resource j and D(i, j) is the maximum demand of resource type j from process i.
D) Only request a resource when it is really needed.

Given a virtual memory system with 4 page frames, how many page faults occur with the Least-Recently Used replacement strategy when pages are accessed in the following order: 1, 2, 3, 4, 5, 1, 3, 4, 2, 3, 1, 5, 4.

A) 7
B) 9
C) 11
D) 13

Which of the following memory management tasks can be performed by the MMU:

A) Memory protection
B) Page table lookup
C) TLB lookup
D) Page replacement

Consider the pseudocode below. Which of the following alternatives are possible in
an environment with other processes P2 and P3 potentially accessing the semaphores S1 and S2.

semaphore S1 = 1 //protects resource R1
semaphore S2 = 1 //protects resource R2

process P1 {
while (true) {
wait(S1)
wait(S2)
//Critical section acccessing resources R1 and R2
signal(S1)
signal(S2)
}
}

A) A deadlock may occur if another process invokes wait on S1 and S2 in the wrong
order.
B) A deadlock may occur if another process invokes signal on S1 and S2 in the
wrong order.
C) A race condition may occur if another process omits to call wait on one of the
semaphores.
D) A race condition may occur if another process spuriously calls signal on one of
the semaphores

Which of the following strategies can help with Thrashing?

A) Using a local replacement algorithm
B) Increase the degree of multiprogramming
C) Using a priority replacement algorithm
D) Decreasing the degree of multiprogramming

Which of the following operations will result in a system call for a normal operating system?

A) Reading the value of a variable stored on the stack
B) Creating a new file
C) Allocating memory on the heap
D) Performing a jump (JMP) instruction

Which of the terms below refer to methods used for allocation of disk space for a file?
A) Virtual allocation
B) Indexed allocation
C) Segment allocation
D) Contiguous allocation

Which of the following statements are true about microkernels?

A) A microkernel runs entirely in user space.
B) Microkernels allow more operating system services to run in user space.
C) Microkernels need to provide process management.
D) Microkernels need to provide file system services.

Consider the program below. How many times will it output “A”?

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main() {
setbuf(stdout, NULL); //disable buffering
pid_t pid1 = fork();
if (pid1 == 0) {
pid_t pid2 = fork();
pid_t pid3 = fork();
if (pid3 == 0) {
printf("A");
}
}
printf("A");
}

A) 5 times
B) 6 times
C) 7 times
D) 8 times

—————————————————————————————————————————

10/30 identiska frågor med 2017-2022 Quizet

4/30 frågor vi ej kan.
