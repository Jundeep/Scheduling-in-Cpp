#include <iostream>
#include <queue>
using namespace std;

struct Process {
    int pid;            // Process ID
    int burst_time;     // Burst time required for the process
    int priority;       // Priority of the process
    int remaining_time; // Remaining time of the process
};

int main() {
    // Input values
    int num_processes, quantum;
    cout << "Enter number of processes: ";
    cin >> num_processes;
    cout << "Enter quantum: ";
    cin >> quantum;

    // Queues for the two levels
    queue<Process> q1, q2;

    // Read processes and push them into the first-level queue
    for (int i = 0; i < num_processes; i++) {
        Process p;
        cout << "Process ID, Burst time, Priority (0 is highest): ";
        cin >> p.pid >> p.burst_time >> p.priority;
        p.remaining_time = p.burst_time;
        q1.push(p);
    }

    int current_time = 0;

    // Scheduling loop
    while (!q1.empty() || !q2.empty()) {
        if (!q1.empty()) {
            // Execute the highest priority process in the first-level queue
            Process& p = q1.front();
            int time_quantum = min(quantum, p.remaining_time);
            p.remaining_time -= time_quantum;
            current_time += time_quantum;

            // If process completed, print message
            if (p.remaining_time == 0) {
                cout << "Process " << p.pid << " completed at time " << current_time << endl;
                q1.pop();
            } else {
                // Move the process to the second-level queue
                p.priority++;
                q2.push(p);
                q1.pop();
            }
        } else {
            // Execute the process at the front of the second-level queue
            Process& p = q2.front();
            int time_quantum = min(quantum, p.remaining_time);
            p.remaining_time -= time_quantum;
            current_time += time_quantum;

            // If process completed, print message
            if (p.remaining_time == 0) {
                cout << "Process " << p.pid << " completed at time " << current_time << endl;
                q2.pop();
            } else {
                // Move the process to the end of the second-level queue
                q2.push(p);
                q2.pop();
            }
        }
    }

    return 0;
}
