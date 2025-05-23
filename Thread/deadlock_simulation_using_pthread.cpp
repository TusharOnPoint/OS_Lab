#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

struct Account {
    string name;
    int balance;
};

void* transfer1(void* arg) {
    Account* a = (Account*)arg;

    pthread_mutex_lock(&lock1);
    cout << a[0].name << " locked\n";
    sleep(1);
    pthread_mutex_lock(&lock2);
    cout << a[1].name << " locked\n";

    a[0].balance -= 100;
    a[1].balance += 100;

    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);

    pthread_exit(nullptr);
}

void* transfer2(void* arg) {
    Account* a = (Account*)arg;

    pthread_mutex_lock(&lock2);
    cout << a[1].name << " locked\n";
    sleep(1);
    pthread_mutex_lock(&lock1);
    cout << a[0].name << " locked\n";

    a[1].balance -= 200;
    a[0].balance += 200;

    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);

    pthread_exit(nullptr);
}

int main() {
    pthread_t t1, t2;
    Account accs[2] = {{"Tushar", 500}, {"Borshon", 500}};

    pthread_create(&t1, nullptr, transfer1, accs);
    pthread_create(&t2, nullptr, transfer2, accs);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);

    cout << "Final Balances:\n";
    cout << accs[0].name << ": " << accs[0].balance << "\n";
    cout << accs[1].name << ": " << accs[1].balance << "\n";

    return 0;
}
