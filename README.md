# TDDE47 Pintos

_Every individual lab have a separate branch_

- **Lab 0** - Complete
- **Lab 1** - Complete
- **Lab 2** - Complete
- **Lab 3** - Complete
- **Lab 4** - Complete
- **Lab 5** - Complete
- **Lab 6** - Complete

# Exam cheatsheet

- _Book:_ https://www.download.booksfree.org/download-book/?dlm-dp-dl=24807
- _Flashcards:_ https://quizlet.com/705419294/tddb68-flash-cards/ (Not provided by me)

## Processes and threads

\*Chapter **3.1-3.4**, **4.1-4.3**, **4.5**, **13.1**, **14.1-2\***

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

![Process state](https://raw.githubusercontent.com/simon-bonnedahl/TDDE47-pintos/main/images/process-state.png)

### Multithreading

Multithreading in Pintos involves the creation of multiple threads within a process that can execute concurrently. Each thread has its own stack, register set, and thread control block (TCB) containing information such as its ID, state, and priority. Pintos uses a priority-based scheduling algorithm to determine which thread should execute next, and threads can synchronize their execution using synchronization primitives such as mutex locks and semaphores. Multithreading allows for improved performance and efficiency by enabling parallel execution of tasks within a process. However, it also requires careful management of shared resources and synchronization to prevent race conditions and ensure correct program behavior.

## CPU Scheduling

\*Chapter **5.1-5.5**, **5.8\***

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
  -- Processes are executed based on their priority, where the higher priority process is executed first. A priority is assigned to each process based on its characteristics or dynamically based on its behavior.
- **Multilevel Queue Scheduling**
  -- Processes are categorized into multiple queues based on their characteristics, such as their priority or CPU requirements, and are executed in a pre-determined order. Each queue may have a different scheduling algorithm.
- **Multilevel Feedback Queue**
  -- Multilevel feedback queue is a scheduling algorithm where processes are assigned to different queues based on their priority, and each queue has a different scheduling algorithm. Processes move between queues based on their CPU usage and priority, which helps to balance the workload and improve system performance.

### Generalised Processor Sharing (GPS)

Generalized Processor Sharing (GPS) is a scheduling algorithm that allocates processor time to processes based on their weight. Each process is assigned a weight, which determines the fraction of processor time it will receive. Processes with higher weights receive more processor time, and GPS guarantees that all processes receive a minimum share of the processor time, which helps to prevent starvation.

**Pros:**

- Proportional fairness
- Work conserving

**Cons:**

- Non preemption
- Non-zero time quanta
- Not knowing when the next (high-priority) job arrives

## Synchronisation

\*Chapter **6.1-6.7**, **7.1-7.3\***

### Race conditions

Race conditions occur in concurrent programming when two or more threads access a shared resource simultaneously, and the order in which they access the resource affects the correctness of the program. Race conditions can lead to unexpected and unpredictable behavior such as incorrect output, program crashes, or data corruption. Race conditions arise because of the non-deterministic nature of concurrent execution, which can cause threads to execute in different orders each time the program runs. To prevent race conditions, synchronization mechanisms such as locks, semaphores, and barriers are used to coordinate access to shared resources and ensure that only one thread can access the resource at a time.

### Critical-Section Problem

The critical section problem is a synchronization problem that arises when multiple threads or processes access a shared resource. The problem is to ensure that only one thread at a time executes the critical section of the code, which accesses the shared resource, to prevent race conditions and ensure data consistency. Various synchronization techniques, such as mutex locks or semaphores, can be used to implement mutual exclusion and ensure that only one thread executes the critical section at a time.

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

### Spinlocks

A spinlock is a synchronization technique used in multi-threaded programming to protect shared resources from concurrent access by multiple threads. A spinlock is essentially a busy-wait loop, in which a thread repeatedly checks a lock variable to see if it has been acquired by another thread. If the lock is currently held by another thread, the waiting thread continues to spin (loop) until the lock becomes available. Once the lock is acquired, the thread can access the shared resource or enter a critical section of code.
Spinlocks are a form of **mutual exclusion** mechanism that can be implemented in software or hardware. They are commonly used in real-time systems, where the overhead of context switching between threads or processes can be high, and in situations where waiting for a lock for a short period of time is expected to be more efficient than switching to another thread. However, excessive spinning can lead to high CPU utilization and can cause performance problems.

### Atomic Operation

An atomic operation is an operation that appears to be executed as a single, indivisible unit of operation, without the possibility of interruption by other threads or processes. In other words, it is a single operation that cannot be divided or interrupted, and it is always executed in its entirety or not executed at all. Atomic operations are used in multi-threaded or multi-process programming to ensure that certain operations, such as memory access or variable manipulation, are performed atomically and are not subject to race conditions or inconsistencies. They are typically implemented using low-level hardware or operating system primitives, such as atomic instructions or synchronization primitives like **mutex locks**.

### Hardware Support

**TestAndSet** is a synchronization instruction used to implement mutual exclusion and prevent race conditions. It is an **atomic operation** that reads the value of a boolean variable, sets it to true, and returns its previous value. This operation is used to acquire a lock on a shared resource or enter a **critical section**. If the previous value of the boolean variable was true, it means that another thread already has the lock, and the current thread must wait until the lock is released. This operation is often used in low-level synchronization primitives, such as **spinlocks** or **mutex locks**.

## Memory

\*Chapter **9**, **10.1-10.3\***

### Paging

Paging is a memory management scheme used by operating systems to manage physical memory by dividing it into fixed-size blocks called "pages" and virtual memory into fixed-size blocks called "page frames". When a process requires memory, it is allocated a set of contiguous virtual pages, which are mapped to physical pages by the operating system. Pages that are not currently in use are swapped out to disk to make space for new pages. Paging allows the operating system to allocate memory efficiently and provide virtual memory to each process, allowing it to use more memory than is physically available. It also helps to prevent memory **fragmentation** and improves memory utilization by enabling sharing of pages between multiple processes.

![Paging](https://raw.githubusercontent.com/simon-bonnedahl/TDDE47-pintos/main/images/paging.png)

### Page faults

A page fault occurs when a program tries to access a memory page that is not currently in physical memory. The operating system resolves the fault by fetching the required page from secondary storage and loading it into physical memory. Once the page is loaded, the operating system updates the page table and allows the program to continue execution. Page faults are a normal part of memory management and occur frequently in most programs.

![Page faults](https://raw.githubusercontent.com/simon-bonnedahl/TDDE47-pintos/main/images/page-fault.png)

### MMU

The Memory Management Unit (MMU) is a hardware component in a computer system that is responsible for translating virtual memory addresses used by the software running on the system into physical memory addresses used by the computer's RAM.

The MMU's purpose is to provide an abstraction layer between the software and the physical memory of the system, allowing the software to access a larger address space than the physical memory actually provides. The MMU achieves this by creating a mapping between virtual memory addresses and physical memory addresses, and intercepting all memory access requests from the software to perform the necessary translation.

The MMU also provides memory protection and memory allocation management features. It can enforce memory protection policies by marking pages of memory as read-only, read-write, or no access, and can trigger a memory access violation exception when the software attempts to access memory in violation of these policies. Additionally, the MMU can manage the allocation and deallocation of physical memory pages, by creating and removing mappings between virtual and physical addresses as needed, and handling page faults when the software requests a page that is not currently mapped in physical memory.

Overall, the MMU plays a critical role in managing the memory of a computer system, enabling efficient use of physical memory, providing memory protection, and enabling the use of virtual memory.

### Page replacement algorithms

- **First-In-First-Out(FIFO)**
  -- Replaces the oldest page. Exhibits **Belady's anomaly**
- **Least Recently Used**
  -- Replaces the page that **has not been** used for the longest period of time. **Avoids Belady's anomaly**
- **Optimal replacement (Belady's algoritm)**
  -- Replaces the page that **will not be used** for the longest period of time. Is only optimal if there are no
  "dirty write-backs". **Avoids Belady's anomaly**

### Belady's Anomaly

Belady's anomaly is a situation where adding more memory frames to a system can actually increase the number of page faults, despite the common intuition that more memory should always result in fewer page faults. This occurs because some page replacement algorithms can behave in unexpected ways when more memory is available, resulting in a counterintuitive increase in the number of page faults. However, this phenomenon is not always observed in practice and is a theoretical result that occurs only in certain circumstances.

### Trashing

Trashing is a term used to describe a situation in which a computer system spends a significant amount of time and resources moving data between physical memory (RAM) and secondary storage, such as a hard disk. This occurs when the system is overcommitted and does not have enough physical memory to hold all of the data it needs to process.

When a computer system starts trashing, its performance can degrade significantly, as it spends a large portion of its time swapping data between RAM and secondary storage instead of actually processing the data. This can result in slower response times, increased latency, and a decrease in overall system throughput.

Trashing is often caused by running too many memory-intensive programs simultaneously, or by running programs that require more memory than is available on the system. To avoid trashing, it is important to monitor system memory usage and adjust the number and types of programs running on the system as needed to ensure that there is always enough physical memory available for the system to operate efficiently.

### Memory Protection

Memory protection is a mechanism that prevents processes from accessing memory regions they are not authorized to access, using hardware features such as the Memory Management Unit (MMU). It helps ensure system stability and security by preventing processes from interfering with each other and accessing sensitive data.

### Memory Compression

Memory compression is a technique used by operating systems to increase the effective amount of physical memory available to a system by compressing data in memory. When memory is running low, the operating system can compress some of the least frequently used pages of memory and store them in a compressed format in physical memory. This frees up physical memory for other applications and can improve system performance by reducing the amount of data that needs to be swapped out to disk. When a compressed page is needed, the operating system can decompress it on the fly and load it back into physical memory.

### Segmentation

Segmentation is a memory management technique used by operating systems to divide a process's logical address space into multiple segments, each of which contains a specific type of data, such as code or data. Each segment is assigned a base address and a length, which are used to map logical addresses to physical addresses. This allows processes to be divided into logical units, which can be independently managed and protected from other processes. Segmentation can help prevent buffer overflow attacks and simplify memory allocation, but it can also lead to **fragmentation** and **overhead** in the memory management system. Segmentation is often used in combination with paging to provide a more flexible and efficient memory management solution.

### Translation Lookaside Buffer (TLB)

The Translation Lookaside Buffer (TLB) is a hardware cache used by the CPU to speed up virtual address translation. When a program accesses memory, it uses virtual addresses, which must be translated by the CPU into physical addresses before they can be used to access memory. The TLB is a cache that stores recently used virtual-to-physical address translations, so the CPU can quickly access the physical address without having to consult the page table. This speeds up memory access and improves system performance. When a virtual address is not found in the TLB, the CPU must consult the page table to retrieve the physical address, which takes longer than a TLB hit.

## Virtualization

### Layering

### Microkernels

### Kernel modules

### Implementations

- **Emulation**
- **Hypervisor-based virtualization**
- **Paravirtualization**
- **Programming environment virtualization**
- **Application containment**

### Hypervisor-based virtualization

## File System

### Inode

### Hadoop Distributed File System (HDFS)

### Virtual File System (VFS)

### File Control Block (FCB)

### Allocation Methods

- **Contiguous allocation**
- **Indexed allocation**
- **Linked allocation**

### File-Allocation Table (FAT)

### Linked list

### Journaling

### Snapshot

# Terms

- **Fragmentation** is
- **Overhead** is
- **Mutual Exclusion** is
-
