#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;

struct Process {
    int pid;
    int arrival;
    int burst;
    int remaining;
    int completion = 0;
    int turnaround = 0;
    int waiting = 0;
};

int main() {
    int n, timeQuantum;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter time quantum: ";
    cin >> timeQuantum;

    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        cout << "Process " << i + 1 << " Arrival Time: ";
        cin >> processes[i].arrival;
        cout << "Process " << i + 1 << " Burst Time: ";
        cin >> processes[i].burst;
        processes[i].pid = i + 1;
        processes[i].remaining = processes[i].burst;
    }

    queue<int> readyQueue;
    int currentTime = 0;
    int completed = 0;
    vector<bool> inQueue(n, false);
    vector<int> gantt_processes;

    for (int i = 0; i < n; i++) {
        if (processes[i].arrival <= currentTime) {
            readyQueue.push(i);
            inQueue[i] = true;
        }
    }

    while (completed < n) {
        if (readyQueue.empty()) {
            gantt_processes.push_back(0);
            currentTime++;
            
            for (int i = 0; i < n; i++) {
                if (!inQueue[i] && processes[i].arrival <= currentTime && processes[i].remaining > 0) {
                    readyQueue.push(i);
                    inQueue[i] = true;
                }
            }
            continue;
        }

        int idx = readyQueue.front();
        readyQueue.pop();

        int execTime = min(timeQuantum, processes[idx].remaining);

        for (int t = 0; t < execTime; t++) {
            gantt_processes.push_back(processes[idx].pid);
        }

        currentTime += execTime;
        processes[idx].remaining -= execTime;

        for (int i = 0; i < n; i++) {
            if (!inQueue[i] && processes[i].arrival <= currentTime && processes[i].remaining > 0) {
                readyQueue.push(i);
                inQueue[i] = true;
            }
        }

        if (processes[idx].remaining > 0) { // not finished yet
            readyQueue.push(idx);
        } else {
            processes[idx].completion = currentTime;
            processes[idx].turnaround = processes[idx].completion - processes[idx].arrival;
            processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;
            completed++;
        }
    }

    double total_tat = 0, total_wt = 0;

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (auto &p : processes) {
        total_tat += p.turnaround;
        total_wt += p.waiting;
        cout << p.pid << "\t" << p.arrival << "\t" << p.burst << "\t"
             << p.completion << "\t" << p.turnaround << "\t" << p.waiting << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Turnaround Time: " << total_tat / n << endl;
    cout << "Average Waiting Time: " << total_wt / n << endl;

    cout << "\nGantt Chart:\n|";
    int last_pid = -1;
    for (int pid : gantt_processes) {
        if (pid != last_pid) {
            if (pid == 0)
                cout << " Idle |";
            else
                cout << " P" << pid << " |";
            last_pid = pid;
        }
    }
    
    cout << "\n0";
    last_pid = gantt_processes[0];
    int length = 1;
    for (size_t i = 1; i <= gantt_processes.size(); i++) {
        if (i == gantt_processes.size() || gantt_processes[i] != last_pid) {
            cout << setw(5) << length;
            if (i < gantt_processes.size())
                last_pid = gantt_processes[i];
        }
        length++;
    }

    return 0;
}

// sample input 
/*
Enter number of processes: 3
Enter time quantum: 2
Process 1 Arrival Time: 0
Process 1 Burst Time: 5
Process 2 Arrival Time: 1
Process 2 Burst Time: 3
Process 3 Arrival Time: 2
Process 3 Burst Time: 4
*/

// sample output
/*
PID     AT      BT      CT      TAT     WT
1       0       5       12      12      7
2       1       3       9       8       5
3       2       4       11      9       5

Average Turnaround Time: 9.67
Average Waiting Time: 5.67

Gantt Chart:
| P1 | P2 | P3 | P1 | P2 | P3 | P1 |
0    2    4    6    8    9   11   12
*/