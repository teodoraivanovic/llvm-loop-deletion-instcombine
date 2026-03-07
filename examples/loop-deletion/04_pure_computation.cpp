int pure_dead_computation() {
    int x = 5;
    int y = 10;
    
    // no live exit values, finite trip count, no side effects => DELETE - ok
    for (int i = 0; i < 100; i++) {
        int temp = x * y;
        x = temp % 7;
        y = x + 3;
    }

    return 999;
}

int main() {
    return pure_dead_computation();
}
