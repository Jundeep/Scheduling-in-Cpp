#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

struct Process {
    int pid;        
    int priority;   
    int burstTime;  
    int remainingTime; 
    int arrivalTime; 
};


class ComparePriority {
public:
    bool operator()(Process& p1, Process& p2) {
        return p1.priority < p2.priority;
    }
};


class CompareArrivalTime {
public:
    bool operator()(Process& p1, Process& p2) {
        return p1.arrivalTime > p2.arrivalTime;
    }
};


void roundRobinScheduling(queue<Process>& q, int quantum) {
    int time = 0;
    while(!q.empty()) {
        Process p = q.front();
        q.pop();
        if(p.remainingTime <= quantum) {
            time += p.remainingTime;
            cout << "Process " << p.pid << " completed execution at time " << time << endl;
        } else {
            time += quantum;
            p.remainingTime -= quantum;
            q.push(p);
        }
    }
}


void twoLevelScheduling(priority_queue<Process, vector<Process>, ComparePriority>& q1, queue<Process, deque<Process> > & q2, int quantum) {
    int time = 0;
    while(!q1.empty()) {
        Process p = q1.top();
        q1.pop();
        cout << "Process " << p.pid << " with priority " << p.priority << " is executing at time " << time << endl;
        if(p.remainingTime <= quantum) {
            time += p.remainingTime;
            cout << "Process " << p.pid << " completed execution at time " << time << endl;
        } else {
            time += quantum;
            p.remainingTime -= quantum;
            q2.push(p);
        }
        
        if(!q1.empty() && q1.top().priority > p.priority) {
            cout << "Process " << p.pid << " preempted by process " << q1.top().pid << " at time " << time << endl;
            q1.push(p);
            twoLevelScheduling(q1, q2, quantum);
            return;
        }
    }
    roundRobinScheduling(q2, quantum);
}

int main() {
    int n, quantum;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the quantum for Round Robin scheduling: ";
    cin >> quantum;
    priority_queue<Process, vector<Process>, ComparePriority> q1;
    queue<Process, deque<Process> > q2;
    for(int i=0; i<n; i++) {
        Process p;
        cout << "Enter the process id, priority, burst time, and arrival time of process " << i+1 << ": ";
        cin >> p.pid >> p.priority >> p.burstTime >> p.arrivalTime;
        p.remainingTime = p.burstTime;
        q1.push(p);
    }
    twoLevelScheduling(q1, q2, quantum);
    return 0;
}
