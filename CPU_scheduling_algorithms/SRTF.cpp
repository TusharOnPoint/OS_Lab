#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>

using namespace std;

struct Process {
    int pid;
    int arrival;
    int burst;
    int remaining;
    int completion;
    int turnaround;
    int waiting;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; ++i) {
        cout << "Process " << i + 1 << " Arrival Time: ";
        cin >> processes[i].arrival;
        cout << "Process " << i + 1 << " Burst Time: ";
        cin >> processes[i].burst;
        processes[i].pid = i + 1;
        processes[i].remaining = processes[i].burst;
    }

    int completed = 0, current_time = 0;
    vector<int> gantt_processes;

    while (completed != n) {
        int idx = -1;
        int min_remaining = INT_MAX;

        // Finding a process with minimum remaining burst time
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrival <= current_time &&
                processes[i].remaining > 0 &&
                processes[i].remaining < min_remaining) {
                min_remaining = processes[i].remaining;
                idx = i;
            }
        }

        if (idx != -1) { // found a process with minimum remaining time 
            gantt_processes.push_back(processes[idx].pid);
            processes[idx].remaining--;
            current_time++;

            if (processes[idx].remaining == 0) { // completed
                processes[idx].completion = current_time;
                processes[idx].turnaround = processes[idx].completion - processes[idx].arrival;
                processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;
                completed++;
            }
        } else { // not found any process
            gantt_processes.push_back(0);
            current_time++;
        }
    }

    double total_tat = 0, total_wt = 0;

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (const auto& p : processes) {
        total_tat += p.turnaround;
        total_wt += p.waiting;
        cout << p.pid << "\t" << p.arrival << "\t" << p.burst << "\t"
             << p.completion << "\t" << p.turnaround << "\t" << p.waiting << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Turnaround Time: " << total_tat / n << endl;
    cout << "Average Waiting Time: " << total_wt / n << endl;

    cout << "\nGantt Chart:\n|";
    for (size_t i = 0; i < gantt_processes.size(); ++i) {
        if (i == 0 || gantt_processes[i] != gantt_processes[i - 1]) {
            if (gantt_processes[i] == 0)
                cout << " Idle |";
            else
                cout << " P" << gantt_processes[i] << " |";
        }
    }

    cout << "\n0";
    int last_pid = gantt_processes[0];
    for (size_t i = 1; i <= gantt_processes.size(); ++i) {
        if (i == gantt_processes.size() || gantt_processes[i] != last_pid) {
            cout << "     " << i;
            if (i < gantt_processes.size())
                last_pid = gantt_processes[i];
        }
    }

    return 0;
}


/*Enter number of processes: 3
Process 1 Arrival Time: 0
Process 1 Burst Time: 6
Process 2 Arrival Time: 1
Process 2 Burst Time: 2
Process 3 Arrival Time: 2
Process 3 Burst Time: 8

PID     Arrival Burst   Completion  Turnaround  Waiting
1       0       6       16          16          10
2       1       2       3           2           0
3       2       8       24          22          14

Average Turnaround Time: 13.33
Average Waiting Time: 8.00

Gantt Chart:
| P1 | P2 | P1 | P3 |
0    1    3    16   24
*/
