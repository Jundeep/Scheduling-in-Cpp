#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct Process {
    int pid;              // Process ID
    int burst_time;       // Burst time required for the process
    int priority;         // Priority of the process
    int remaining_time;   // Remaining time of the process
};

int main() {
    int num_processes;
    cout << "Enter the number of processes: ";
    cin >> num_processes;

    queue<Process> q1;    // First-level queue for fixed priority preemptive scheduling
    queue<Process> q2;    // Second-level queue for round robin scheduling

    // Getting inputs for the processes
    for (int i = 1; i <= num_processes; i++) {
        Process p;
        cout << "Process " << i << ":\n";
        cout << "Process ID: ";
        cin >> p.pid;
        cout << "Burst time: ";
        cin >> p.burst_time;
        cout << "Priority (0 is highest): ";
        cin >> p.priority;
        p.remaining_time = p.burst_time;
        q1.push(p);
    }

    int quantum;
    cout << "Enter the quantum for round robin scheduling: ";
    cin >> quantum;

    int current_time = 0;

    while (!q1.empty() || !q2.empty()) {
        if (!q1.empty()) { // First-level queue has priority
            Process current_process = q1.front();
            q1.pop();

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
                current_process.priority++;
                q2.push(current_process);
            }
        }
        else if (!q2.empty()) { // First-level queue is empty, use second-level queue
            Process current_process = q2.front();
            q2.pop();

            // Execute the process for the required time quantum
            int time_quantum = min(quantum, current_process.remaining_time);
            current_process.remaining_time -= time_quantum;
            current_time += time_quantum;

            // Check if the process has completed execution
            if (current_process.remaining_time == 0) {
                cout << "Process " << current_process.pid << " completed execution at time " << current_time << "\n";
            }
            else {
                // Move the process to the end of the second-level queue
                q2.push(current_process);
            }
        }
        else { // No more processes to execute
            current_time++;
        }
    }

    return 0;
}
