#include <cstdio>

using namespace std;

int main() {
    for (int i = 1; i < 100; i++) {
        if (!(i % 2) || !(i % 3)) {  //_________
            continue;
        }
        printf("%d ", i);
    }
}