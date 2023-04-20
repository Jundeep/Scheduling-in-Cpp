#include <iostream>
#include <queue>
using namespace std;

struct Process {
    int pid;            
    int burst_time;     
    int priority;       
    int remaining_time; 
};

int main() {
    
    int num_processes, quantum;
    cout << "Enter number of processes: ";
    cin >> num_processes;
    cout << "Enter quantum: ";
    cin >> quantum;

    
    queue<Process> q1, q2;

    
    for (int i = 0; i < num_processes; i++) {
        Process p;
        cout << "Process ID, Burst time, Priority (0 is highest): ";
        cin >> p.pid >> p.burst_time >> p.priority;
        p.remaining_time = p.burst_time;
        q1.push(p);
    }

    int current_time = 0;

    
    while (!q1.empty() || !q2.empty()) {
        if (!q1.empty()) {
            
            Process& p = q1.front();
            int time_quantum = min(quantum, p.remaining_time);
            p.remaining_time -= time_quantum;
            current_time += time_quantum;

            
            if (p.remaining_time == 0) {
                cout << "Process " << p.pid << " completed at time " << current_time << endl;
                q1.pop();
            } else {
                
                p.priority++;
                q2.push(p);
                q1.pop();
            }
        } else {
            
            Process& p = q2.front();
            int time_quantum = min(quantum, p.remaining_time);
            p.remaining_time -= time_quantum;
            current_time += time_quantum;

            
            if (p.remaining_time == 0) {
                cout << "Process " << p.pid << " completed at time " << current_time << endl;
                q2.pop();
            } else {
                
                q2.push(p);
                q2.pop();
            }
        }
    }

    return 0;
}
