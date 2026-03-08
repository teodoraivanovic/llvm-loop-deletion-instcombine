int infinite_loop_test() {
    int count = 0;

    // finite trip count BUT...
    while (1) {
        count++;
        if (count > 1000000) {  // ... this condition is runtime-dependent => ALIVE
            break;
        }
    }

    return count;
}

// truly infinite with no exit => ALIVE
void truly_infinite() {
    int x = 0;
    while (1) {
        x = (x + 1) % 100;
    }
}

int main() {
    truly_infinite();
    return infinite_loop_test();
}
