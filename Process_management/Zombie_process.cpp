#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        cout << "Child process (PID " << getpid() << ") exiting..." << endl;
        exit(0);
    } else if (pid > 0) {
        cout << "Parent process (PID " << getpid() << ") sleeping for 30 seconds..." << endl;
        sleep(30);
        cout << "Parent woke up, exiting without wait()." << endl;
    } else {
        cout << "Fork failed." << endl;
    }

    return 0;
}
