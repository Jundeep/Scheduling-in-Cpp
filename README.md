Q_-Design a scheduling program to implements a Queue with two levels:
   Level 1 : Fixed priority preemptive Scheduling
   Level 2 : Round Robin Scheduling
   For a Fixed priority preemptive Scheduling (Queue 1), the Priority 0 is highest priority. If one process P1 is scheduled and running, another process P2 with higher priority comes. The New process (high priority) process P2 preempts currently running process P1 and process P1 will go to second level queue. Time for which process will strictly execute must be considered in the multiples of 2.
   All the processes in second level queue will complete their execution according to round robin scheduling.
   Consider: 1. Queue 2 will be processed after Queue 1 becomes empty.
   2. Priority of Queue 2 has lower priority than in Queue 1.

Ans_-

Here is an explanation to the question-


This question is asking you to design a program that implements a scheduling algorithm using two levels of queues. The first level of the queue uses fixed priority preemptive scheduling, where the process with the highest priority (priority 0) will be executed first. If a process with a higher priority arrives while a lower priority process is already running, the higher priority process will preempt the lower priority process and the lower priority process will be moved to the second level queue.

The second level of the queue uses round-robin scheduling, which means that each process in the queue will execute for a fixed amount of time (called the time quantum) before being preempted and moved to the end of the queue.

The program should first read in the number of processes and the time quantum from the user. Then it should read in the details of each process (process ID, burst time, and priority) and add it to the first-level queue.

The program should then run a scheduling loop until both the first-level and second-level queues are empty. In each iteration of the loop, the program should check if there are any processes in the first-level queue. If there are, it should execute the process with the highest priority. If a higher priority process arrives while a lower priority process is running, the lower priority process should be moved to the second-level queue. If there are no processes in the first-level queue, the program should execute the process at the front of the second-level queue.

The program should output a message each time a process completes execution, including the process ID and the time at which it completed. Once all processes have completed execution, the program should exit.
