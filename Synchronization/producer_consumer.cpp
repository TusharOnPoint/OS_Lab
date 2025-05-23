#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <chrono>
using namespace std;

queue<int> buffer;
const unsigned int MAX_SIZE = 5;
mutex mtx;

bool stop = false;

void producer() {
    int value = 0;
    while (!stop) {
        mtx.lock();
        if (buffer.size() < MAX_SIZE) {
            buffer.push(value);
            cout << "Produced: " << value << endl;
            value++;
        }
        mtx.unlock();

        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void consumer() {
    while (!stop) {
        mtx.lock();
        if (!buffer.empty()) {
            int item = buffer.front();
            buffer.pop();
            cout << "Consumed: " << item << endl;
        }
        mtx.unlock();

        this_thread::sleep_for(chrono::milliseconds(150));
    }
}

int main() {
    thread t1(producer);
    thread t2(consumer);

    this_thread::sleep_for(chrono::seconds(5));
    stop = true;

    t1.join();
    t2.join();

    return 0;
}
