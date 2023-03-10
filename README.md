# TDDE47 Pintos

## **->** *Every individual lab have a separate branch* **<-**

- **Lab 0** - Complete
- **Lab 1** - Complete
-  **Lab 2** - Complete
-  **Lab 3** - Complete
- **Lab 4** - Complete
- **Lab 5** - Complete
- **Lab 6** - Complete

# Exam cheatsheet

- *Book:* https://www.download.booksfree.org/download-book/?dlm-dp-dl=24807
- *Flashcards:* https://quizlet.com/705419294/tddb68-flash-cards/


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

### Multithreading
Multithreading in Pintos involves the creation of multiple threads within a process that can execute concurrently. Each thread has its own stack, register set, and thread control block (TCB) containing information such as its ID, state, and priority. Pintos uses a priority-based scheduling algorithm to determine which thread should execute next, and threads can synchronize their execution using synchronization primitives such as mutex locks and semaphores. Multithreading allows for improved performance and efficiency by enabling parallel execution of tasks within a process. However, it also requires careful management of shared resources and synchronization to prevent race conditions and ensure correct program behavior.

## Scheduling

*Chapter 5.1-5.5, 5.8*

### Preemption
Preemption is the ability of an operating system to interrupt a running process in order to allocate resources to a higher-priority process. This allows the system to manage resources efficiently and ensure that critical tasks are completed in a timely manner. Preemption can be voluntary, when a process willingly yields the CPU, or involuntary, when the system forcibly suspends a process. Preemption is often implemented using hardware interrupts, and is a fundamental feature of modern operating systems, enabling them to provide responsive and fair service to all processes.

### Scheduling Algorithms
 - **First come, First served (FCFS)**
 -- The simplest scheduling algorithm, where processes are executed in the order they arrive, and the next process is selected only when the current process has completed.
- **Shortest-Job-First (SJF)**
 -- Processes are executed based on the length of their CPU burst, where the process with the shortest **burst time** is executed first.
- **Round Robin (RR)**
-- A time-sharing scheduling algorithm where each process is allocated a fixed time slice and is executed in a circular order. If a process does not complete its execution within the time slice, it is **preempted** and added to the end of the ready queue.
- **Priority Scheduling**
--	Processes are executed based on their priority, where the higher priority process is executed first. A priority is assigned to each process based on its characteristics or dynamically based on its behavior.
- **Multilevel Queue Scheduling**
-- Processes are categorized into multiple queues based on their characteristics, such as their priority or CPU requirements, and are executed in a pre-determined order. Each queue may have a different scheduling algorithm.


### Bankers
## Synchronisation

### Race conditions
Race conditions occur in concurrent programming when two or more threads access a shared resource simultaneously, and the order in which they access the resource affects the correctness of the program. Race conditions can lead to unexpected and unpredictable behavior such as incorrect output, program crashes, or data corruption. Race conditions arise because of the non-deterministic nature of concurrent execution, which can cause threads to execute in different orders each time the program runs. To prevent race conditions, synchronization mechanisms such as locks, semaphores, and barriers are used to coordinate access to shared resources and ensure that only one thread can access the resource at a time.

### Semaphores
Semaphores are a synchronization primitive used to coordinate access to shared resources among multiple threads. They are implemented as a data structure that consists of a counter and a queue of threads waiting to acquire the semaphore. Threads attempt to acquire the semaphore before accessing a shared resource, and if the semaphore counter is zero, indicating the resource is being used by another thread, the thread is blocked and added to the queue of waiting threads. When the semaphore is released, one of the waiting threads is unblocked and allowed to acquire the semaphore. Semaphores are fundamental tools for preventing race conditions in concurrent programming and ensuring safe access to shared resources in operating systems.

### Mutex locks
Mutex locks are a synchronization primitive used to prevent multiple threads from concurrently accessing shared resources. In an operating system, a mutex lock is implemented as a data structure that is associated with a shared resource. A thread that wants to access the resource attempts to acquire the mutex lock, which prevents other threads from accessing the resource until the lock is released. If another thread tries to acquire the lock while it is held by another thread, it is blocked and added to a queue of waiting threads. When the thread holding the lock releases it, one of the waiting threads is unblocked and allowed to acquire the lock. Mutex locks are essential tools for preventing race conditions and ensuring safe access to shared resources in concurrent programming.

### Semaphores vs Locks

The main difference between mutex locks and semaphores is their level of complexity and the scope of their use in synchronization. Mutex locks are simpler than semaphores and are typically used for protecting access to a single shared resource. They provide mutual exclusion and allow only one thread to access the protected resource at a time. In contrast, semaphores are more complex and can be used for synchronization between multiple threads and across multiple resources. They provide a general synchronization mechanism and can be used for signaling and coordination between threads.

Another difference is in their implementation. Mutex locks are typically implemented as binary semaphores, which have a counter of either 0 or 1. When a thread holds the lock, the counter is set to 1, and when it releases the lock, the counter is set to 0. In contrast, semaphores have a counter that can be greater than 1, which allows multiple threads to acquire the semaphore.

In summary, mutex locks are simpler, have a narrower scope, and are used for protecting access to a single shared resource, while semaphores are more complex, have a wider scope, and can be used for synchronization between multiple threads and resources.

### Barriers
Barriers in operating systems are synchronization mechanisms that allow multiple threads to wait for each other to reach a particular point of execution before proceeding. Barriers are commonly used in parallel programming to synchronize the execution of multiple threads, where each thread needs to wait for others to complete a specific task before proceeding to the next stage of execution. A barrier is typically initialized with the number of threads that need to reach the barrier before they can proceed. When a thread reaches the barrier, it waits until all other threads also reach the barrier. Once all threads have reached the barrier, they are released and can proceed with their execution.

### Deadlocks
Deadlocks in operating systems occur when two or more threads or processes are blocked and unable to proceed because each is waiting for the other to release a resource that it has acquired. Deadlocks arise when resources are shared among multiple threads or processes, and each requires exclusive access to multiple resources to complete its execution. If the resources are not released in the correct order or at the right time, a situation can arise where none of the threads can proceed, resulting in a deadlock. Deadlocks can cause the system to become unresponsive, and resolving them requires careful management of resource allocation and synchronization to avoid circular dependencies.

## Memory

### Paging
Paging is a memory management scheme used by operating systems to manage physical memory by dividing it into fixed-size blocks called "pages" and virtual memory into fixed-size blocks called "page frames". When a process requires memory, it is allocated a set of contiguous virtual pages, which are mapped to physical pages by the operating system. Pages that are not currently in use are swapped out to disk to make space for new pages. Paging allows the operating system to allocate memory efficiently and provide virtual memory to each process, allowing it to use more memory than is physically available. It also helps to prevent memory fragmentation and improves memory utilization by enabling sharing of pages between multiple processes.



## Virtualization




