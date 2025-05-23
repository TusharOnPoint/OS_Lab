#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
using namespace std;
mutex forks[5];
bool stop = false;

void philosopher(int id) {
    int left = id;
    int right = (id + 1) % 5;

    while (!stop) {
        cout << "Philosopher " << id << " is thinking.\n";
        this_thread::sleep_for(chrono::milliseconds(100 + rand() % 100));

        if (id == 5 - 1) {
            forks[right].lock();
            forks[left].lock();
        } else {
            forks[left].lock();
            forks[right].lock();
        }
        cout << "Philosopher " << id << " is eating.\n";
        this_thread::sleep_for(chrono::milliseconds(100 + rand() % 100));

        forks[left].unlock();
        forks[right].unlock();
    }
}

int main() {
    vector<thread> philosophers;
    for (int i = 0; i < 5; i++) {
        philosophers.push_back(thread(philosopher, i));
    }
    this_thread::sleep_for(chrono::seconds(5));
    stop= true;
    for (auto& p : philosophers) {
        p.join();
    }

    return 0;
}
