#include <iostream>

inline int computeValue(int x) {
    return x * x;
}

int main() {
    int result = 0;
    
    // After inlining, this loop has no side effects
    for (int i = 0; i < 50; i++) {
        result = computeValue(i);  // Overwritten each time
    }
    
    // We only use the final value, but it is overwritten and never actually used
    std::cout << "Done" << std::endl;
    
    return 0;
}