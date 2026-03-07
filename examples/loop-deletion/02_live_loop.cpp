int live_loop_test() {
    int sum = 0;

    for (int i = 0; i < 10; i++) {
        sum += i;
    }

    // alive exit value => ALIVE - ok
    return sum;
}

int main() {
    return live_loop_test();
}