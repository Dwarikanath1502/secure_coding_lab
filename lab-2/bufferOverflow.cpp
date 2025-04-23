// Implement a buffer overflow attack on a C/C++ program and demonstrate how an
// attacker can overwrite memory.

#include <iostream>
#include <cstring>
using namespace std;

void vulnerableFunction() {
    char buffer[10];
    cout << "Enter something (max 10 chars): ";
    cin >> buffer; // No bounds checking!
    cout << "You entered: " << buffer << endl;
}

int main() {
    vulnerableFunction();
    return 0;
}
