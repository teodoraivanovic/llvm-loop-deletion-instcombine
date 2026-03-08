#include <cstdint>

// 1. Same Comparison: x < 10 && x < 10 => x < 10
bool redundant_and(int x) { return x < 10 && x < 10; }

// 2. Range subsumption: x < 10 && x < 20 => x < 10
bool subsume_and(int x) { return x < 10 && x < 20; }

// 3. Always True: x == x => true
bool always_true(int x) { return x == x; }

// 4. Select to Abs: x < 0 ? -x : x => llvm.abs
int32_t manual_abs(int32_t x) { return x < 0 ? -x : x; }

// 5. Min Folding: x < y ? x : y => llvm.minnum
int32_t manual_min(int32_t x, int32_t y) { return x < y ? x : y; }

// 6. Boolean XOR: a != b (for bools) => a ^ b
bool bool_xor(bool a, bool b) { return a != b; }

// 7. Comparison with Max: x > INT32_MAX => false
bool over_limit(int32_t x) { return x > 2147483647; }

// 8. Zero Check: x != 0 || x == 0 => true
bool check_zero(int x) { return x != 0 || x == 0; }

// 9. Sign Bit Check: x < 0 => (x >> 31) & 1
bool is_negative(int32_t x) { return x < 0; }

// 10. Logical Negation: !(x > y) => x <= y
bool not_greater(int x, int y) { return !(x > y); }
