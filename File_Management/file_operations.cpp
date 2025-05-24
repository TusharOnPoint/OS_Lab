#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

int main() {
    // 1. Create a file
    ofstream file("file.txt");
    file << "Hello, file!";
    file.close();
    cout << "File created.\n";

    // 2. Copy the file
    ifstream src("file.txt", ios::binary);
    ofstream dst("copy.txt", ios::binary);
    dst << src.rdbuf();
    src.close();
    dst.close();
    cout << "File copied.\n";

    // 3. Move the file (rename)
    rename("copy.txt", "moved.txt");
    cout << "File moved.\n";

    // 4. Delete files
    remove("file.txt");
    remove("moved.txt");
    cout << "Files deleted.\n";

    return 0;
}
