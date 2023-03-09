# TDDE47 Pintos

Every individual lab have a separate branch


- Lab 0 - Complete
- Lab 1 - Complete
- Lab 2 - Complete
- Lab 3 - Complete
- Lab 4 - Complete
- Lab 5 - Complete
- Lab 6 - Complete

# Exam cheatsheet

*Book:* https://www.download.booksfree.org/download-book/?dlm-dp-dl=24807
*Flashcards:* https://quizlet.com/705419294/tddb68-flash-cards/


## Processes and threads 
*Chapter 3.1-3.4, 4.1-4.3, 4.5, 13.1, 14.1-2*

### Differences
Threads and processes are both used in operating systems to achieve parallelism and to perform multiple tasks simultaneously. However, they differ in how they are managed and how they share resources.

A process is a program in execution, with its own memory space and system resources allocated by the operating system. Processes are managed independently by the operating system, and each process runs in its own address space. This means that a process cannot directly access the memory or resources of another process.

On the other hand, a thread is a lightweight unit of execution within a process, sharing the same memory space and system resources with other threads in the same process. Threads are managed by the operating system within the process, and can communicate and share resources more easily than processes.

One advantage of using threads over processes is that threads can be created and destroyed more quickly than processes, as they share the same memory space and do not need to allocate separate system resources. This makes threads more efficient for tasks that require a high level of concurrency or parallelism, such as performing calculations or processing data in real time.

However, because threads share the same memory space, they can be more susceptible to race conditions and other synchronization issues. Processes, on the other hand, are more isolated from each other and are less likely to interfere with each other's memory or resources. Additionally, processes can take advantage of multiple processors or cores, whereas a single-threaded process can only run on one core at a time.

In summary, processes and threads both have their advantages and disadvantages, and the choice between them depends on the specific requirements of the task at hand.

### Process Control Block (PCB)
The Process Control Block (PCB) is a data structure used by operating systems to manage information about each process in the system. It contains essential details such as process ID, memory allocation, CPU usage, and scheduling information. The PCB is created when a new process is started, and the operating system updates it as the process runs. The PCB is crucial for the operating system to manage process execution, including scheduling, context switching, and synchronization. It enables the operating system to keep track of and manage all the processes running in the system, ensuring they are allocated necessary resources and run efficiently.

### Process state

![Process state](https://raw.githubusercontent.com/simon-bonnedahl/TDDE47-pintos/main/images/SCR-20230309-j8d.png)


## Scheduling

### Preemption
Preemption is the ability of an operating system to interrupt a running process in order to allocate resources to a higher-priority process. This allows the system to manage resources efficiently and ensure that critical tasks are completed in a timely manner. Preemption can be voluntary, when a process willingly yields the CPU, or involuntary, when the system forcibly suspends a process. Preemption is often implemented using hardware interrupts, and is a fundamental feature of modern operating systems, enabling them to provide responsive and fair service to all processes.

### Bankers
## Synchronisation

### Semaphores

### Mutex locks


## Deadlocks

## Memory



## Virtualization
