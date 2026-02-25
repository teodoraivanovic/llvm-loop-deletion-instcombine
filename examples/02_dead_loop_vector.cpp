#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec(100);
    int unused = 0;
    
    // This loop will be deleted - no observable side effects
    for (int i = 0; i < 100; i++) {
        unused += i * i;
    }
    
    std::cout << "Vector size: " << vec.size() << std::endl;
    
    return 0;
}