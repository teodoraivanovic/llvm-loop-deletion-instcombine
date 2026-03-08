#include <cstdint>

// 1. Add Identity: x + 0 => x
uint32_t add_zero(uint32_t x) { return x + 0; }

// 2. Sub Identity: x - x => 0
uint32_t sub_self(uint32_t x) { return x - x; }

// 3. Constant Folding/Reassociation: (x + 5) + 10 => x + 15
uint32_t reassociate(uint32_t x) { return (x + 5) + 10; }

// 4. Subtraction to Negation: 0 - x => -x
int32_t zero_minus(int32_t x) { return 0 - x; }

// 5. Negation of Negation: -(-x) => x
int32_t double_neg(int32_t x) { return -(-x); }

// 6. Multiplication by 1: x * 1 => x
uint32_t mul_one(uint32_t x) { return x * 1; }

// 7. Multiplication by 0: x * 0 => 0
uint32_t mul_zero(uint32_t x) { return x * 0; }

// 8. Distributive Law: (x * 2) + (x * 3) => x * 5
uint32_t distribute(uint32_t x) { return (x * 2) + (x * 3); }

// 9. Division by Self: x / x => 1 (LLVM assumes x != 0 or marks as UB)
uint32_t div_self(uint32_t x) { return x / x; }

// 10. Combined Offset: (x + 1) - (y + 1) => x - y
uint32_t offset_cancel(uint32_t x, uint32_t y) { return (x + 1) - (y + 1); }
