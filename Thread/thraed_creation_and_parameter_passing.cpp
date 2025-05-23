#include <iostream>
#include <thread>
using namespace std;

void sayHello(const string& name, int age) {
    cout << "Hello, " << name << "! You are " << age << " years old.\n";
}

int main() {
    // Creaion and parameter passing 
    thread t(sayHello, "Tushar", 22);
    t.join(); // thread join

    cout << "Main thread finished.\n";
    return 0;
}
