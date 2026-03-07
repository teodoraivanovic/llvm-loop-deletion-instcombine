int local_memory_dead() {
    int array[100];
    
    // storing in the array but it's local and never used after
    for (int i = 0; i < 100; i++) {
        array[i] = i * i;
    }
    
    return 555;
}

int main() {
    return local_memory_dead();
}
