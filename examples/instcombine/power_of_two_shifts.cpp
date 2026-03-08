#include <cstdint>

// 1. Mul to Shift: x * 16 => x << 4
uint32_t mul_pow2(uint32_t x) { return x * 16; }

// 2. Div to Shift: x / 8 => x >> 3
uint32_t div_pow2(uint32_t x) { return x / 8; }

// 3. Mod to AND: x % 4 => x & 3
uint32_t mod_pow2(uint32_t x) { return x % 4; }

// 4. Shift Redundancy: (x << 5) >> 5 => x & 0x07FFFFFF
uint32_t shift_clear(uint32_t x) { return (x << 5) >> 5; }

// 5. Power of 2 Comparison: (x & 7) == 8 => false
bool cmp_impossible(uint32_t x) { return (x & 7) == 8; }

// 6. Log2-style Check: x < 32 && x >= 0 (implicitly)
bool is_small(uint32_t x) { return x / 32 == 0; }

// 7. Bit Rotation: (x << 24) | (x >> 8) => llvm.fshl (Funnel Shift)
uint32_t rotate(uint32_t x) { return (x << 24) | (x >> 8); }

// 8. Multiple Shifts: (x << 2) << 3 => x << 5
uint32_t shift_merge(uint32_t x) { return (x << 2) << 3; }

// 9. Masking before Shift: (x & 0xFF) << 24 => x << 24
uint32_t mask_shift(uint32_t x) { return (x & 0xFF) << 24; }

// 10. Exact Division: (x * 4) / 4 => x
uint32_t exact_div(uint32_t x) { return (x * 4) / 4; }
