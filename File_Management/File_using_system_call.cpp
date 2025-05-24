#include <iostream>
#include <windows.h>
using namespace std;

int main() {
    LPCSTR original = "file.txt";
    LPCSTR copy = "copy.txt";
    LPCSTR moved = "moved.txt";

    // 1. Create and write to file
    HANDLE hFile = CreateFileA(original, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile != INVALID_HANDLE_VALUE) {
        DWORD written;
        const char* data = "Hello, Windows file!";
        WriteFile(hFile, data, strlen(data), &written, NULL);
        CloseHandle(hFile);
        cout << "File created.\n";
    } else {
        cerr << "Failed to create file.\n";
    }

    // 2. Copy file
    if (CopyFileA(original, copy, FALSE)) {
        cout << "File copied.\n";
    } else {
        cerr << "Failed to copy file.\n";
    }

    // 3. Move file
    if (MoveFileA(copy, moved)) {
        cout << "File moved.\n";
    } else {
        cerr << "Failed to move file.\n";
    }

    // 4. Delete files
    if (DeleteFileA(original)) cout << "Original deleted.\n";
    if (DeleteFileA(moved)) cout << "Moved copy deleted.\n";

    return 0;
}
