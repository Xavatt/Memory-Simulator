# Memory-Simulator
Second Project of the class (Operating System)


## OBJECTIVE

The goal of this project is to implement a simulator for virtual memory manager. The simulator reads a file with memory references, called a memory trace, and the proceeds to simulate the memory access in a system that consists of a small **Translation LookAhed Buffer (TLB)**. The simulator reports the total number of memory frames used, and the *average access time* for the entire trace.

To verify you read all events in the trace it ir recommended that you also keep tract of the total number of events(memory accesses) in the trace.

---

## GOALS

The implementation of the cirtual memory simulator will test your comprehension of the interactions between elements in a simple memory hierarchy, as well as verify thta the student is capable of using basic data structures, file management, and general programming methodologies.

## PROBLEM STATEMENT

We are required to implement a *virtual memory simulator* for a system with 16-bit virtual addresses (64Kbytes total) and 8Kbytes of physical memory. Futthermore, assume that the pages and frames are 512-bytes each. To reduce the access time the system has an 8-entry
TLB. The TLB uses the Least Recently Used (LRU) replacement policy to evict entries. To
simplify your implementation you can use a single-level page table for the virtual to physical
address translation. Given the previous conditions your system will have 128 entries in the
page table and a total of 16 frames in memory.

Our simulator must keep track of what pages are loaded into memory. As it processes each
memory event from the trace, it should check if the reference is in the TLB and also check if
the corresponding page is in memory or not. If not, it should choose a frame to remove from
memory. Of course, if the frame to be replaced is dirty, it must be saved to disk. Finally, the
new frame is loaded into memory from disk, and the page table is updated.

Our program will take as input a text file with an **arbitrary** number of memory references.
The first line in the file has the main memory access time (**tmem**), the TLB access time (**ttlb**), and the page fault penalty (tfault). All times are in nano seconds. After the first line, each line will have a 16-bit address followed by the access type (read or write). As an example consider the following four memory references: