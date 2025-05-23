#include <iostream>
#include <thread>
using namespace std;

void calculateSumAndProduct(int a, int b, int* sum, int* product) {
    *sum = a + b;
    *product = a * b;
}

int main() {
    int a = 4, b = 5;
    int sum = 0, product = 0;

    thread t(calculateSumAndProduct, a, b, &sum, &product);
    t.join();
    cout << "Sum = " << sum << "\n";
    cout << "Product = " << product << "\n";

    return 0;
}
