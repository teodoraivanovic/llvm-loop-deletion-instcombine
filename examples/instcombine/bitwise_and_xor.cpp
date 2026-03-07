#include <cstdint>

// 1. XOR Identity: x ^ x => 0
uint32_t xor_self(uint32_t x) { return x ^ x; }

// 2. XOR with 0: x ^ 0 => x
uint32_t xor_zero(uint32_t x) { return x ^ 0; }

// 3. Double XOR: (x ^ y) ^ y => x
uint32_t xor_cancel(uint32_t x, uint32_t y) { return (x ^ y) ^ y; }

// 4. AND with All Ones: x & 0xFFFFFFFF => x
uint32_t and_ones(uint32_t x) { return x & 0xFFFFFFFF; }

// 5. AND with Zero: x & 0 => 0
uint32_t and_zero(uint32_t x) { return x & 0; }

// 6. OR Identity: (x | y) & x => x
uint32_t or_and_absorb(uint32_t x, uint32_t y) { return (x | y) & x; }

// 7. XOR to NOT: x ^ -1 => ~x
uint32_t xor_to_not(uint32_t x) { return x ^ 0xFFFFFFFF; }

// 8. Bitwise De Morgan: ~(~a & ~b) => a | b
uint32_t de_morgan(uint32_t a, uint32_t b) { return ~(~a & ~b); }

// 9. Redundant Mask: (x & 5) & 7 => x & 5
uint32_t mask_redundant(uint32_t x) { return (x & 5) & 7; }

// 10. XOR Constant Folding: (x ^ 1) ^ 2 => x ^ 3
uint32_t xor_reassociate(uint32_t x) { return (x ^ 1) ^ 2; }
