int nested_dead_loops() {
    int result = 0;
    
    // finite trip count, no side effects, no live exit values => DELETE - ok
    for (int i = 0; i < 10; i++) {
        int inner_sum = 0;
        
        // technically this one is alive because we use inner_sum later in the outer loop
        // but since the outer loop is dead, this one will be deleted as well
        for (int j = 0; j < 5; j++) {
            inner_sum += j;
        }
        
        result = inner_sum * 2;
    }

    return 7;
}

int main() {
    return nested_dead_loops();
}
