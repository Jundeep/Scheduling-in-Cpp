#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std;

struct Process {
    int pid;        // Process ID
    int burst_time; // Burst time required for the process
    int priority;   // Priority of the process
    int arrival_time; // Arrival time of the process
    int remaining_time; // Remaining time of the process
};

// Custom comparator for the priority queue
struct ComparePriority {
    bool operator()(Process const& p1, Process const& p2)
    {
        return p1.priority < p2.priority;
    }
};

int main()
{
    int num_processes;
    cout << "Enter the number of processes: ";
    cin >> num_processes;

    queue<Process> queue1; // First-level queue for fixed priority preemptive scheduling
    queue<Process> queue2; // Second-level queue for round robin scheduling

    // Getting inputs for the processes
    for (int i = 1; i <= num_processes; i++) {
        Process p;
        cout << "Process " << i << ":\n";
        cout << "Process ID: ";
        cin >> p.pid;
        cout << "Arrival time: ";
        cin >> p.arrival_time;
        cout << "Burst time: ";
        cin >> p.burst_time;
        cout << "Priority (0 is highest): ";
        cin >> p.priority;
        p.remaining_time = p.burst_time;
        queue1.push(p);
    }

    int quantum;
    cout << "Enter the quantum for round robin scheduling: ";
    cin >> quantum;

    int current_time = 0;
    queue<Process> current_queue; // The current queue being processed

    while (!queue1.empty() || !queue2.empty()) {

        if (!queue1.empty()) { // First-level queue has priority
            current_queue = queue1;
            while (!queue1.empty() && queue1.front().arrival_time <= current_time) {
                current_queue.push(queue1.front());
                queue1.pop();
            }
        }
        else if (!queue2.empty()) { // First-level queue is empty, use second-level queue
            current_queue = queue2;
        }

        if (current_queue.empty()) { // No more processes to execute
            current_time++;
            continue;
        }

        // Sort the queue according to priority
        priority_queue<Process, vector<Process>, ComparePriority> pq;
        while (!current_queue.empty()) {
            pq.push(current_queue.front());
            current_queue.pop();
        }

        // Get the process with highest priority
        Process current_process = pq.top();
        pq.pop();

        // Execute the process for the required time quantum
        int time_quantum = min(quantum, current_process.remaining_time);
        current_process.remaining_time -= time_quantum;
        current_time += time_quantum;

        // Check if the process has completed execution
        if (current_process.remaining_time == 0) {
            cout << "Process " << current_process.pid << " completed execution at time " << current_time << "\n";
        }
        else {
            // Move the process to the second-level queue
            if (!queue2.empty() && queue2.back().pid == current_process.pid) {
                queue2.back().remaining_time = current_process.remaining_time;
            }
            else {
                current_process.priority++;
                queue2.push(current_process);
            }
        }
    }

    return 0;
}
