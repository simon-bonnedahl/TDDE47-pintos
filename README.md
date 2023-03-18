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
- _Exam Questions:_ https://github.com/simon-bonnedahl/TDDE47-pintos/tree/main/exam-questions

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

Multithreading involves the creation of multiple threads within a process that can execute concurrently. Each thread has its own stack, register set, and thread control block (TCB) containing information such as its ID, state, and priority. Pintos uses a priority-based scheduling algorithm to determine which thread should execute next, and threads can synchronize their execution using synchronization primitives such as mutex locks and semaphores. Multithreading allows for improved performance and efficiency by enabling parallel execution of tasks within a process. However, it also requires careful management of shared resources and synchronization to prevent race conditions and ensure correct program behavior.

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

### MMU

The Memory Management Unit (MMU) is a hardware component in a computer system that is responsible for translating virtual memory addresses used by the software running on the system into physical memory addresses used by the computer's RAM.

The MMU's purpose is to provide an abstraction layer between the software and the physical memory of the system, allowing the software to access a larger address space than the physical memory actually provides. The MMU achieves this by creating a mapping between virtual memory addresses and physical memory addresses, and intercepting all memory access requests from the software to perform the necessary translation.

The MMU also provides memory protection and memory allocation management features. It can enforce memory protection policies by marking pages of memory as read-only, read-write, or no access, and can trigger a memory access violation exception when the software attempts to access memory in violation of these policies. Additionally, the MMU can manage the allocation and deallocation of physical memory pages, by creating and removing mappings between virtual and physical addresses as needed, and handling page faults when the software requests a page that is not currently mapped in physical memory.

Overall, the MMU plays a critical role in managing the memory of a computer system, enabling efficient use of physical memory, providing memory protection, and enabling the use of virtual memory.

### Page replacement

Page replacement is a technique used by operating systems to manage memory when the physical memory becomes full. When a process requests a page that is not present in physical memory, the operating system must choose a page to evict from physical memory to make room for the requested page. This is called page replacement.
The operating system uses a page replacement algorithm to select the page to be evicted. The goal of the algorithm is to choose the page that is least likely to be used in the near future to minimize the impact on performance. When a page is selected for replacement, the operating system writes the page's contents back to disk if it has been modified, and then frees the page's frame in physical memory to be used for other pages. The requested page is then loaded into the freed frame in physical memory.

### Page replacement algorithms

- **First-In-First-Out(FIFO)**
  -- Replaces the oldest page. Exhibits **Belady's anomaly**
- **Least Recently Used**
  -- Replaces the page that **has not been** used for the longest period of time. Avoids **Belady's anomaly**
- **Optimal replacement (Belady's algoritm)**
  -- Tries to replace the page that **will not be used** for the longest period of time. Is only optimal if there are no
  "dirty write-backs". Avoids **Belady's anomaly**

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

### Memory mapping

Memory mapping is a technique used by operating systems to allow a process to access a file as if it were in memory, rather than on disk. In this technique, the operating system creates a mapping between a region of virtual memory in the process and a region of the file on disk. This allows the process to read and write to the file as if it were accessing memory directly.

Memory-mapped files offer several benefits, including:

**Improved Performance:**
Memory-mapped files can provide faster access to data than traditional file access methods because data is accessed directly from memory instead of being loaded into and out of memory in blocks. This is particularly useful when working with large files, as only the required portion of the file is loaded into memory.

**Simplified Programming:**
Memory-mapped files simplify programming because they allow files to be treated as if they were part of the process's memory. This means that the same memory access techniques used for data in memory can be used for data in files.

**Sharing Data:**
Memory-mapped files can be used to share data between processes because multiple processes can map the same region of the file into their address space. This can be useful for inter-process communication and can help to reduce the memory usage of a system.

**Persistence:**
Memory-mapped files can be used to persist data across process boundaries because changes made to the mapped memory are automatically written back to the file on disk. This can simplify the task of storing and retrieving data between runs of a program.

### Segmentation

Segmentation is a memory management technique used by operating systems to divide a process's logical address space into multiple segments, each of which contains a specific type of data, such as code or data. Each segment is assigned a base address and a length, which are used to map logical addresses to physical addresses. This allows processes to be divided into logical units, which can be independently managed and protected from other processes. Segmentation can help prevent buffer overflow attacks and simplify memory allocation, but it can also lead to **fragmentation** and **overhead** in the memory management system. Segmentation is often used in combination with paging to provide a more flexible and efficient memory management solution.

### Translation Lookaside Buffer (TLB)

The Translation Lookaside Buffer (TLB) is a hardware cache used by the CPU to speed up virtual address translation. When a program accesses memory, it uses virtual addresses, which must be translated by the CPU into physical addresses before they can be used to access memory. The TLB is a cache that stores recently used virtual-to-physical address translations, so the CPU can quickly access the physical address without having to consult the page table. This speeds up memory access and improves system performance. When a virtual address is not found in the TLB, the CPU must consult the page table to retrieve the physical address, which takes longer than a TLB hit.

## Virtualization

### Layering

The layering approach to virtualization is a technique that involves dividing the virtualization process into layers, each of which is responsible for a specific aspect of the virtualization process. Each layer provides a level of abstraction that enables the layer above it to access resources in a simplified and standardized way, independent of the underlying hardware.

The layers in a virtualization stack typically include the hardware layer, hypervisor layer, guest operating system layer, and application layer. The hardware layer provides access to the underlying physical hardware, while the hypervisor layer provides the virtualization layer and manages the virtual machines running on the physical hardware. The guest operating system layer provides a virtualized operating system environment, and the application layer runs on top of the virtualized operating system.

The layering approach allows each layer to focus on its specific function, making it easier to develop, test, and maintain each layer separately. It also provides a high degree of flexibility, as each layer can be replaced or updated independently of the other layers. This approach is commonly used in hypervisor-based virtualization, where the hypervisor layer provides the virtualization layer and isolates the guest operating systems from the underlying physical hardware.

### Microkernels

Microkernels are a type of operating system kernel architecture that is designed to be small and minimalist, providing only the essential services required to manage hardware resources and inter-process communication. The microkernel approach contrasts with **monolithic kernel architectures**, which implement a wide range of services and device drivers in the kernel.

In a microkernel architecture, the kernel provides only basic services such as **inter-process communication**, process management, and memory management. Other services, such as device drivers and file system management, are implemented as separate processes running outside the kernel. This design reduces the complexity and size of the kernel, making it more secure and easier to maintain.

**Pros:**

- **Easier to extend a microkernel**
  – **Easier to port the operating system to new architectures**
  – **More reliable (less code is running in kernel mode)**
  – **More secure**

**Cons:**

- **Performance overhead of user space to kernel space communication**
- **More complicated synchronization**

### Kernel modules

Kernel modules, also known as loadable kernel modules (LKMs), are software components that can be dynamically loaded and unloaded into the kernel of an operating system to provide additional functionality, such as device drivers or file system support. Kernel modules are particularly useful in Linux and other Unix-like operating systems, where the kernel is designed to be small and modular.

**Pros:**

- **Reduced kernel size**
  – **Simplified kernel development**
  – **Increased flexibility**
  – **Improved system performance**

**Cons:**

- **Security risks**
  – **Complexity**
  - **Incompatibility**
  - **Performance overhead**

### Implementations of virtualization

- **Emulation**
- **Hypervisor-based virtualization**
- **Paravirtualization**
- **Programming environment virtualization**
- **Application containment**

### Hypervisor-based virtualization

Hypervisor-based virtualization is a virtualization technique that allows multiple operating systems to run on a single physical machine, each in its own isolated virtual environment. This is achieved by using a layer of software called a hypervisor or a virtual machine monitor (VMM) that sits between the hardware and the operating systems being virtualized. The hypervisor provides virtualized hardware resources to each operating system, including CPU, memory, and I/O devices. Each operating system runs as if it has full access to the physical hardware, but in reality, it is running in its own isolated environment created by the hypervisor. This provides a flexible and efficient way to consolidate multiple workloads onto a single physical machine, improving resource utilization and reducing hardware costs.

## File System

### Inode

An inode (short for "index node") is a data structure used by file systems in operating systems to store information about a file or directory. Each file or directory on a file system is represented by an inode.

Inodes typically contain information such as the file's owner, permissions, size, timestamps, and pointers to the actual data blocks on disk where the file's contents are stored. When a user requests to read or write a file, the operating system uses the inode to locate the file's data blocks on disk.

Inodes are an important part of file system design because they enable efficient storage and retrieval of file metadata, as well as quick access to the data blocks that make up a file.

### Virtual File System (VFS)

The Virtual File System (VFS) is an abstraction layer in an operating system that provides a consistent interface for accessing different types of file systems. It achieves this by providing a set of generic file system operations, such as opening, reading, and writing files, that can be implemented differently by different file systems. The VFS allows applications and system components to access files on different types of file systems without having to know the details of each file system, and enables the operating system to support multiple file systems simultaneously. This makes it easier to manage and use multiple storage systems in a consistent way.

### File Control Block (FCB)

A File Control Block (FCB) is a data structure used by an operating system to manage information about a file. It contains information such as the file name, location, size, creation and modification dates, and permissions. The FCB is created when a file is opened and is used to keep track of the file's status and location in memory. It also contains pointers to the file's data blocks on disk, making it possible to read and write data to the file. The FCB is typically used by the operating system's file system driver to manage file operations and ensure data integrity.

### Allocation Methods

- **Contiguous allocation**
  -- This method involves storing files as contiguous blocks of data on the disk. When a file is created, the file system identifies a contiguous block of free space on the disk that is large enough to hold the entire file, and assigns it to the file. This method is simple and fast, but can lead to fragmentation over time as files are deleted and new files are added.
- **Indexed allocation**'
  -- This method involves storing files in a table, or index, of data blocks. Each file has its own index, which contains pointers to the locations of the data blocks on the disk. This method allows for fast access to individual data blocks, but requires additional disk space to store the index, which can be a disadvantage when dealing with large numbers of small files.
- **Linked allocation**
  -- This method involves storing files as a linked list of data blocks on the disk. Each block in the file contains a pointer to the next block in the file, and the final block contains a pointer to a special end-of-file marker. This method allows files to be stored in non-contiguous blocks, reducing fragmentation, but can lead to poor performance when reading or writing large files, as the file system needs to follow a chain of pointers to access each block.

### File-Allocation Table (FAT)

The File Allocation Table (FAT) is a file system used by many operating systems, including Windows and DOS. It is a simple and efficient file system that uses a table to keep track of the location of files on a disk. The FAT contains entries for each file on the disk, including the file name, date and time stamps, and a pointer to the first cluster of the file. Each cluster is a fixed-size block of data, and files can span multiple clusters. The FAT allows for quick access to files and efficient use of disk space, but can become fragmented over time, reducing performance.

### Journaling

Journaling file systems are a type of file system that provides a way to recover quickly from system crashes or other interruptions that can cause file system corruption or data loss. They do this by keeping a journal or log of all changes made to the file system. The journal records changes before they are made to the file system, allowing the system to recover quickly by replaying the journal to restore the file system to a consistent state.

When a change is made to the file system, such as creating, deleting or modifying a file, the change is recorded in the journal along with a checksum or hash value. When the system restarts, the file system driver can read the journal to determine if any changes were not completed or were interrupted, and then replay the changes to ensure the file system is consistent.

Journaling file systems are used in many modern operating systems, including Linux, macOS, and Windows. They provide better data integrity and faster recovery times compared to traditional file systems, making them a popular choice for systems that require high reliability and availability.

### Snapshot

A snapshot-based file system is a type of file system that provides a way to create and manage snapshots of the file system at different points in time. A snapshot is a read-only copy of the file system at a specific point in time, allowing users to roll back the file system to that point in time if necessary.

Snapshots are created by taking a copy of the file system's metadata, which includes information about the file system's directories and files, and storing it in a separate location. The file system continues to operate normally, with changes being made to the file system's data blocks, but the metadata of the snapshot remains unchanged.

Snapshots can be used for a variety of purposes, such as system backup, data recovery, or testing. For example, if a user accidentally deletes a file, they can use a snapshot to restore the file to a previous state. Snapshots can also be used for testing changes to the file system or software updates, allowing users to roll back to a previous state if the changes cause issues.

### Snapshot vs Journaling

Snapshot filesystems allow you to save and access read-only copies of a filesystem at different points in time, while journaling filesystems log changes made to the filesystem to ensure data consistency and reliability.

### Readers-writers problem

The Readers-Writers problem is a classic synchronization problem in computer science that deals with multiple threads accessing a shared resource. In this problem, multiple threads need to access a shared resource, but they have different requirements. Readers only need to read the resource, while writers need to modify it.

The problem arises when multiple threads try to access the shared resource simultaneously. If a reader and a writer try to access the resource at the same time, the writer may modify the resource while the reader is still reading it, leading to inconsistent or incorrect data. Similarly, if two writers try to modify the resource at the same time, their changes may conflict with each other, resulting in data loss or corruption.

To solve this problem, synchronization mechanisms such as semaphores, mutexes, or monitors can be used to control access to the shared resource. One common approach is to use a read-write lock, which allows multiple readers to access the resource simultaneously, but only one writer at a time. When a writer needs to modify the resource, it acquires a write lock, which prevents any other thread from accessing the resource until the write operation is completed. When a reader needs to read the resource, it acquires a read lock, which allows multiple readers to access the resource simultaneously, but prevents any writer from modifying it until all the readers have finished reading.

Proper synchronization is crucial to ensure data consistency and integrity in multi-threaded applications. The Readers-Writers problem is a common example of such synchronization challenges, and understanding how to solve it can help developers design more efficient and reliable multi-threaded applications.

### Copy-on-write (COW)

Copy-on-write (COW) is a technique used in computer programming to optimize memory usage by avoiding unnecessary duplication of data. In COW, when a process requests to create a new copy of data, the operating system does not immediately make a full copy of the data. Instead, the operating system creates a copy-on-write reference to the original data, which means that the new copy points to the same physical memory as the original data until the copy is modified. When the new copy is modified, only the modified data is copied to a new location in memory, and the reference to the original data is replaced by a reference to the new copy. This avoids unnecessary copying of data and saves memory space. COW is commonly used in virtual memory systems and file systems to implement efficient sharing of memory and data between processes.

# Terms

- **Fragmentation** is when a file or data is divided into smaller pieces or fragments and scattered across different locations in storage. This can lead to reduced storage efficiency and slower access times, as the computer must search for and retrieve the fragments when they are needed.
- **Overhead** is the additional resources or operations required by a system or process beyond the minimum necessary to achieve a desired outcome. This can include time, memory, or processing power, and can lead to reduced efficiency or performance.
- **Mutual Exclusion** is a mechanism to ensure that only one process or thread can access a shared resource at a time, to prevent race conditions or other synchronization issues. This is typically achieved through the use of locks or other synchronization primitives that prevent multiple processes or threads from accessing the resource simultaneously.
- **Monolithic kernel architectures** is a type of operating system design in which all the operating system's services, such as device drivers, file systems, and memory management, are contained within a single kernel. This approach can provide better performance and simpler design, but can also be less modular and harder to maintain.
- **Inter-process communication** is a mechanism used by operating systems to allow different processes or applications to communicate and share data with each other. This can be achieved through various methods, such as message passing, shared memory, or sockets.
- **Starvation** is a situation that can occur in concurrent systems when a process or thread is unable to access a resource it needs to execute, due to the resource being monopolized by other processes or threads. This can result in the affected process or thread being blocked indefinitely, which can lead to reduced system performance or even a system deadlock.
