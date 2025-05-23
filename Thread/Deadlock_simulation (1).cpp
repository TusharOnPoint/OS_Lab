#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

class Account {
public:
    string name;
    int balance;
    mutex mtx;

    Account(string name, int balance) : name(name), balance(balance) {}

    void deposit(int amount) {
        balance += amount;
    }

    void withdraw(int amount) {
        balance -= amount;
    }
};

// This function causes a deadlock when two threads call it in reverse order
void transfer(Account& from, Account& to, int amount) {
    from.mtx.lock();
    cout << "Locked " << from.name << " for withdrawal\n";
    this_thread::sleep_for(chrono::milliseconds(100));

    to.mtx.lock();
    cout << "Locked " << to.name << " for deposit\n";

    if (from.balance >= amount) {
        from.withdraw(amount);
        to.deposit(amount);
        cout << "Transferred $" << amount << " from " << from.name << " to " << to.name << "\n";
    } else {
        cout << "Insufficient balance in " << from.name << "\n";
    }
    to.mtx.unlock();
    from.mtx.unlock();
}

int main() {
    Account acc1("Altaf", 500);
    Account acc2("Bivas", 500);

    thread t1(transfer, ref(acc1), ref(acc2), 100);
    thread t2(transfer, ref(acc2), ref(acc1), 200);

    t1.join();
    t2.join();

    cout << "Final Balance: Altaf = TK. " << acc1.balance << ", Bivas = TK. " << acc2.balance << "\n";
    return 0;
}

/*
Locked Altaf for withdrawal
Locked Bivas for withdrawal
// deadlock 
*/