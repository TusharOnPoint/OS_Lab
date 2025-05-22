#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int pid, arrival, burst, remaining, priority;
    int completion = 0, turnaround = 0, waiting = 0;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "\nProcess " << p[i].pid << " Arrival Time: ";
        cin >> p[i].arrival;
        cout << "Burst Time: ";
        cin >> p[i].burst;
        cout << "Priority (lower = higher): ";
        cin >> p[i].priority;
        p[i].remaining = p[i].burst;
    }

    int complete = 0, time = 0;
    vector<int> gantt;

    while (complete < n) {
        int idx = -1, minPriority = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                if (p[i].priority < minPriority || (p[i].priority == minPriority && p[i].arrival < p[idx].arrival)) {
                    minPriority = p[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            gantt.push_back(p[idx].pid);
            p[idx].remaining--;
            if (p[idx].remaining == 0) {
                p[idx].completion = time + 1;
                p[idx].turnaround = p[idx].completion - p[idx].arrival;
                p[idx].waiting = p[idx].turnaround - p[idx].burst;
                complete++;
            }
        } else {
            gantt.push_back(-1);
        }

        time++;
    }

    double totalTAT = 0, totalWT = 0;
    cout << "\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n";
    for (auto& x : p) {
        totalTAT += x.turnaround;
        totalWT += x.waiting;
        cout << x.pid << "\t" << x.arrival << "\t" << x.burst << "\t" << x.priority << "\t"
             << x.completion << "\t" << x.turnaround << "\t" << x.waiting << "\n";
    }

    cout << "\nAverage Turnaround Time: " << totalTAT / n;
    cout << "\nAverage Waiting Time: " << totalWT / n;

    // Display Gantt chart
    cout << "\n\nGantt Chart:\n|";
    for (int i = 0; i < gantt.size(); i++) {
        if (gantt[i] == -1) cout << " IDLE |";
        else cout << " P" << gantt[i] << " |";
    }

    cout << "\n0";
    for (int i = 1; i <= gantt.size(); i++) {
        cout << "    " << i;
    }

    cout << "\n";
    return 0;
}

// sample input 
/* Enter number of processes: 3

Process 1 Arrival Time: 0
Burst Time: 5
Priority: 2

Process 2 Arrival Time: 1
Burst Time: 3
Priority: 1

Process 3 Arrival Time: 2
Burst Time: 4
Priority: 2 */

// sample output 
/* 
PID	AT	BT	PR	CT	TAT	WT
1 	0	  5 	2 	11	11	6
2	  1 	3 	1	  4 	3 	0
3 	2 	4 	2 	15	13	9

Average Turnaround Time: 9
Average Waiting Time: 5

Gantt Chart:
| P1 | P1 | P2 | P2 | P2 | P1 | P1 | P3 | P3 | P3 | P3 |
0    1    2    3    4    5    6    7    8    9    10   11
*/
