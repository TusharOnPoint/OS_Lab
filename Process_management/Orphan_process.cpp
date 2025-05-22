#include <iostream>
#include <unistd.h>

using namespace std;

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        sleep(5);  // Wait for parent to exit first
        cout << "Child process (PID " << getpid() << ") is now orphan, adopted by init/systemd. My PPID is " << getppid() << endl;
    } else if (pid > 0) {
        cout << "Parent process (PID " << getpid() << ") exiting immediately..." << endl;
        exit(0);  // Parent exits before child terminated
    } else {
        cout << "Fork failed." << endl;
    }

    return 0;
}
