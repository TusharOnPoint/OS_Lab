#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
using namespace std;

int shared_data = 0;
int reader_count = 0;
mutex mtx, read_mtx;

void reader(int id) {
    while (true) {
        read_mtx.lock();
        reader_count++;
        if (reader_count == 1) mtx.lock();
        read_mtx.unlock();

        // Reading
        cout << "Reader " << id << " is reading: " << shared_data << endl;
        this_thread::sleep_for(chrono::milliseconds(100));

        read_mtx.lock();
        reader_count--;
        if (reader_count == 0) mtx.unlock();
        read_mtx.unlock();

        this_thread::sleep_for(chrono::milliseconds(200));
    }
}

void writer(int id) {
    while (true) {
        mtx.lock();

        // Writing
        shared_data++;
        cout << "Writer " << id << " wrote: " << shared_data << endl;
        this_thread::sleep_for(chrono::milliseconds(150));

        mtx.unlock();

        this_thread::sleep_for(chrono::milliseconds(300));
    }
}

int main() {
    vector<thread> threads;
    for (int i = 1; i <= 3; i++)
        threads.push_back(thread(reader, i));
    for (int i = 1; i <= 2; i++)
        threads.push_back(thread(writer, i));

    for (auto& t : threads) t.join();

    return 0;
}
