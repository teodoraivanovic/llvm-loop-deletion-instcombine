# llvm-loop-deletion-instcombine

This project provides custom **Loop Deletion** and **InstCombine** passes for LLVM.

# Loop Deletion

Loops, and especially complex ones for that matter, can become very heavy and time-consuming during runtime, so the goal (both developer's and compiler's) is to simplify them as much as possible. One of the ways compiler handles those heavy loops is by running the loop-deletion pass during optimization. Loop-deletion pass is a transformation that eliminates dead loops from the Intermediate Representation (IR).

A loop is considered dead if **all** of the following conditions are satisfied:

#### 1. The loop has a finite and computable trip count

That is, the loop's trip count is finite **and** known at compile time. For example, this loop has a computable trip count:

```
for (int i = 0; i < 10; i++) {
    x--;
}
```

Whereas this one doesn't, since we don't know `x` at compile time:

```
while (x > 0) {
    x--;
}
```

#### 2. The loop has no side effects

For example, the loop body must not: do I/O operations, write to memory (unless proven dead), 
call functions with side effects, contain volatile loads/stores, perform atomic operations, throw exceptions etc.

This loop is deletable:

```
for (int i = 0; i < 100; i++) {
    int x = i * 2;
}
```

But this one is not, since there's an I/O operation:

```
for (int i = 0; i < 100; i++) {
    std::cout << i << std::endl;
}
```

#### 3. The loop's computation is not used outside of it

For example, this loop is deletable:

```
int foo() {

    int sum = 0;
    
    for (int i = 0; i < 10; i++) {
        sum += i;
    }
    
    return 0;
}
```

Whereas this one is not:

```
int foo() {

    int sum = 0;
    
    for (int i = 0; i < 10; i++) {
        sum += i;
    }
    
    return sum;
}
```

# InstCombine

InstCombine optimizes mathematical expressions using simple algebra and logic identities.

### Canonize
```
Commutative(Const, X) -> Commutative(X, Const)
```

### Arithmetic
```
X + 0 = X
X - 0 = X
X - X = 0
X * 1 = X
X * 0 = 0
X / 1 = X
```

### Negation
```
-(-X) = X
X + (-Y) = X - Y
X - (-Y) = X + Y
-(X - Y) = Y - X
```

### Logic
```
X & X = X | X = X
X & 1...1 = X
X | 1...1 = 1
X & 0 = 0
X | 0 = X
X xor 0 = X
X xor X = 0
```

### 2^k multiplication/division
```
X * 2^k = X << k
X / 2^k = X >> k
```

# Project Setup & Build

### Setup
```
git clone https://github.com/teodoraivanovic/llvm-loop-deletion-instcombine.git
cd llvm-loop-deletion-instcombine/
```

### Build
```
mkdir -p build/ && cd build/
cmake ..
make -j
```

### Build and run all the tests
```
chmod +x scripts/build_and_test_all.sh
./scripts/build_and_test_all.sh
```

# Authors
Teodora Ivanović 90/2021 \
Lazar Jovanović 69/2022
