#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

using namespace std;

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        execl("/usr/bin/gnome-calculator", "gnome-calculator", NULL);
        cout << "Failed to launch calculator." << endl;
    } else if (pid > 0) {
        cout << "Calculator launched. Press Enter to terminate it..." << endl;
        cin.get();
        kill(pid, SIGKILL);
        wait(NULL);
        cout << "Calculator process terminated." << endl;
    } else {
        cout << "Fork failed." << endl;
    }

    return 0;
}
