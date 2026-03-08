#include <stdio.h>

int loop_with_side_effects() {
    int sum = 0;
    
    // I/O => ALIVE - ok
    for (int i = 0; i < 5; i++) {
        sum += i;
        printf("Iteration %d\n", i);
    }
    
    return 42;
}

int main() {
    return loop_with_side_effects();
}
