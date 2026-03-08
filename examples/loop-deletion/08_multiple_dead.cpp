int multiple_dead_loops() {
    int a = 0, b = 0, c = 0;

    // no side effects, finite loop, no live exit values => DELETE - ok
    for (int i = 0; i < 10; i++) {
        a += i;
    }

    // no side effects, finite loop, no live exit values => DELETE - ok
    for (int j = 0; j < 20; j++) {
        b += j * 2;
    }

    // no side effects, finite loop, no live exit values => DELETE - ok
    for (int k = 0; k < 5; k++) {
        c = c * 3 + 1;
    }
    
    return 12345;
}

int main() {
    return multiple_dead_loops();
}
