#include <iostream>
#include <thread>
#include <string>
using namespace std;

struct Student {
    string name;
    int marks[3];
    float average;
    char grade;
};

void calculateResult(Student* s) {
    int total = 0;
    for (int i = 0; i < 3; i++) {
        total += s->marks[i];
    }

    s->average = total / 3.0f;

    if (s->average >= 90) s->grade = 'A';
    else if (s->average >= 80) s->grade = 'B';
    else if (s->average >= 70) s->grade = 'C';
    else if (s->average >= 60) s->grade = 'D';
    else s->grade = 'F';
}

int main() {
    Student s = {"Tushar", {85, 90, 80}, 0.0f, ' '};

    thread t(calculateResult, &s);
    t.join();

    cout << "Student Name: " << s.name << "\n";
    cout << "Average Marks: " << s.average << "\n";
    cout << "Grade: " << s.grade << "\n";

    return 0;
}
