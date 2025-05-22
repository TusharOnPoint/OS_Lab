#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int pid, arrival, burst;
    int completion = 0, turnaround = 0, waiting = 0;
    bool done = false;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; ++i) {
        p[i].pid = i + 1;
        cout << "\nProcess " << p[i].pid << " Arrival Time: ";
        cin >> p[i].arrival;
        cout << "Burst Time: ";
        cin >> p[i].burst;
    }

    int time = 0, completed = 0;
    vector<int> gantt;

    while (completed < n) {
        int idx = -1;
        int minBurst = 1e9;

        for (int i = 0; i < n; ++i) {
            if (!p[i].done && p[i].arrival <= time) {
                if (p[i].burst < minBurst || (p[i].burst == minBurst && p[i].arrival < p[idx].arrival)) {
                    minBurst = p[i].burst;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            time = max(time, p[idx].arrival);
            p[idx].completion = time + p[idx].burst;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
            time += p[idx].burst;
            p[idx].done = true;
            gantt.push_back(p[idx].pid);
            completed++;
        } else {
            gantt.push_back(-1);
            time++;
        }
    }

    double totalTAT = 0, totalWT = 0;
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (auto& x : p) {
        totalTAT += x.turnaround;
        totalWT += x.waiting;
        cout << x.pid << "\t" << x.arrival << "\t" << x.burst << "\t"
             << x.completion << "\t" << x.turnaround << "\t" << x.waiting << "\n";
    }

    cout << "\nAverage Turnaround Time: " << totalTAT / n;
    cout << "\nAverage Waiting Time: " << totalWT / n;

    cout << "\n\nGantt Chart:\n|";
    int t = 0;
    for (int id : gantt) {
        if (id == -1) cout << " IDLE |";
        else cout << " P" << id << " |";
    }

    cout << "\n0";
    for (int i = 1; i <= gantt.size(); i++) {
        cout << "    " << i;
    }
    cout << "\n";

    return 0;
}
/*
// sample input
Enter number of processes: 4

Process 1 Arrival Time: 0
Burst Time: 5

Process 2 Arrival Time: 1
Burst Time: 3

Process 3 Arrival Time: 2
Burst Time: 4

Process 4 Arrival Time: 2
Burst Time: 3

// sample output

PID     AT      BT      CT      TAT     WT
1       0       5       5       5       0
2       1       3       8       7       4
3       2       4       15      13      9
4       2       3       11      9       6

Average Turnaround Time: 8.5
Average Waiting Time: 4.75

Gantt Chart:
| P1 | P2 | P4 | P3 |
0    1    2    3    4