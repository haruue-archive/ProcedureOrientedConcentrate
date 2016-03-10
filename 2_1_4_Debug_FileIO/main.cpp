#include <iostream>
#include <fstream>

using namespace std;

int main() {
    fstream one("one.txt", ios::out);
    if (!one) {
        cerr << "Write Error." << endl;
        return 0;
    }
    char currentChar;
    while ((currentChar = cin.get()) != EOF) {
        one << currentChar;
    }
    one.close();
    return 0;
}