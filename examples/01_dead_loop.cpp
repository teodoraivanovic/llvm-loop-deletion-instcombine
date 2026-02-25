#include <iostream>

int main() {
    int sum = 0;

    for (int i = 0; i < 1000; i++) {
        sum += i;
    }

    // 'sum' is never used, so the entire loop is dead code
    std::cout << "Hello, World!" << std::endl;

    return 0;
}