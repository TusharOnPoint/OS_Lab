#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Process {
    int pid;
    int arrival;
    int burst;
    int priority;
    int completion;
    int turnaround;
    int waiting;
    bool done = false;
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
        cout << "Process " << i + 1 << " Priority (lower number = higher priority): ";
        cin >> processes[i].priority;
        processes[i].pid = i + 1;
    }

    int current_time = 0, completed = 0;
    vector<pair<int, int>> gantt_chart;

    while (completed != n) {
        int idx = -1;
        int highest_priority = INT_MAX;

        for (int i = 0; i < n; ++i) {
            if (processes[i].arrival <= current_time && !processes[i].done) {
                if (processes[i].priority < highest_priority ||
                    (processes[i].priority == highest_priority && processes[i].arrival < processes[idx].arrival)) {
                    highest_priority = processes[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            gantt_chart.push_back({processes[idx].pid, current_time});
            current_time += processes[idx].burst; // once started complete fully
            processes[idx].completion = current_time;
            processes[idx].turnaround = processes[idx].completion - processes[idx].arrival;
            processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;
            processes[idx].done = true;
            completed++;
        } else {
            gantt_chart.push_back({0, current_time});
            current_time++;
        }
    }

    double total_tat = 0, total_wt = 0;
    cout << "\nPID\tArrival\tBurst\tPriority\tCompletion\tTurnaround\tWaiting\n";
    for (auto &p : processes) {
        total_tat += p.turnaround;
        total_wt += p.waiting;
        cout << p.pid << "\t" << p.arrival << "\t" << p.burst << "\t" << p.priority << "\t\t"
             << p.completion << "\t\t" << p.turnaround << "\t\t" << p.waiting << "\n";
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Turnaround Time: " << total_tat / n << endl;
    cout << "Average Waiting Time: " << total_wt / n << endl;

    cout << "\nGantt Chart:\n|";
    for (size_t i = 0; i < gantt_chart.size(); ++i) {
        if (i == 0 || gantt_chart[i].first != gantt_chart[i - 1].first) {
            if (gantt_chart[i].first == 0)
                cout << " Idle |";
            else
                cout << " P" << gantt_chart[i].first << " |";
        }
    }

    cout << "\n" << gantt_chart[0].second;
    for (size_t i = 1; i < gantt_chart.size(); ++i) {
        if (gantt_chart[i].first != gantt_chart[i - 1].first) {
            cout << setw(6) << gantt_chart[i].second;
        }
    }
    cout << setw(6) << current_time << endl;

    return 0;
}

// sample input 
/* Enter number of processes: 3
Process 1 Arrival Time: 0
Process 1 Burst Time: 5
Process 1 Priority: 2
Process 2 Arrival Time: 1
Process 2 Burst Time: 3
Process 2 Priority: 1
Process 3 Arrival Time: 2
Process 3 Burst Time: 4
Process 3 Priority: 3 */

// sample output 
/* PID     Arrival Burst   Priority    Completion  Turnaround  Waiting
1       0       5        2          8           8           3
2       1       3        1          5           4           1
3       2       4        3          12          10          6

Average Turnaround Time: 7.33
Average Waiting Time: 3.33

Gantt Chart:
| P1 | P2 | P3 |
0     5     8    12  */
