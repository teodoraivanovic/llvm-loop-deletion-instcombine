int dead_loop_test() {
    int sum = 0;

    // no side effects, finite loop, no live exit values => DELETE - ok
    for (int i = 0; i < 10; i++) {
        sum += i;
    }

    return 42;
}

int main() {
    return dead_loop_test();
}
