#include <stdio.h>
#include <stdint.h>



void print_binary_uint8(uint8_t x) {
    for (int i = 7; i >= 0; i--) {
        putchar((x & (1 << i)) ? '1' : '0');
    }
    putchar('\n');
}

const uint8_t m1_8 = 0x55; // 01010101
const uint8_t m2_8 = 0x33; // 00110011
const uint8_t m4_8 = 0x0F; // 00001111

uint8_t popcount8a(uint64_t x)
{
    printf("Initial x: "); print_binary_uint8(x);

    // --- 2-bit groups ---
    uint8_t temp = x & m1_8;
    printf("After x & m1: "); print_binary_uint8(temp);
    temp = x >> 1;
    printf("After x >> 1: "); print_binary_uint8(temp);
    temp = temp & m1_8;
    printf("After (x >> 1) & m1: "); print_binary_uint8(temp);
    x = (x & m1_8) + temp;
    printf("After 2-bit count: "); print_binary_uint8(x);

    // --- 4-bit groups ---
    temp = x & m2_8;
    printf("After x & m2: "); print_binary_uint8(temp);
    temp = x >> 2;
    printf("After x >> 2: "); print_binary_uint8(temp);
    temp = temp & m2_8;
    printf("After (x >> 2) & m2: "); print_binary_uint8(temp);
    x = (x & m2_8) + temp;
    printf("After 4-bit count: "); print_binary_uint8(x);

    // --- 8-bit groups ---
    temp = x & m4_8;
    printf("After x & m4: "); print_binary_uint8(temp);
    temp = x >> 4;
    printf("After x >> 4: "); print_binary_uint8(temp);
    temp = temp & m4_8;
    printf("After (x >> 4) & m4: "); print_binary_uint8(temp);
    x = (x & m4_8) + temp;
    printf("After 8-bit count: "); print_binary_uint8(x);

    return x;

}

uint8_t popcount8b(uint8_t x) {
    printf("Initial x: "); print_binary_uint8(x);

    // --- 2-bit groups ---
    uint8_t temp = x >> 1;
    printf("After x >> 1: "); print_binary_uint8(temp);
    temp = temp & m1_8;
    printf("After (x >> 1) & m1: "); print_binary_uint8(temp);
    x = x - temp;
    printf("After x -= (x >> 1) & m1: "); print_binary_uint8(x);

    // --- 4-bit groups ---
    temp = x & m2_8;
    printf("After x & m2: "); print_binary_uint8(temp);
    uint8_t temp2 = x >> 2;
    printf("After x >> 2: "); print_binary_uint8(temp2);
    temp2 = temp2 & m2_8;
    printf("After (x >> 2) & m2: "); print_binary_uint8(temp2);
    x = temp + temp2;
    printf("After 4-bit count: "); print_binary_uint8(x);

    // --- 8-bit groups ---
    temp = x >> 4;
    printf("After x >> 4: "); print_binary_uint8(temp);
    temp = x + temp;
    printf("After x + (x >> 4): "); print_binary_uint8(temp);
    x = temp & m4_8;
    printf("After (x + (x >> 4)) & m4: "); print_binary_uint8(x);

    // --- Folding ---
    temp = x >> 4;
    printf("After x >> 4 (folding): "); print_binary_uint8(temp);
    x = x + temp;
    printf("After x += x >> 4: "); print_binary_uint8(x);

    x = x & 0x0F; // Mask to 4 bits (since 8-bit max popcount is 8, which fits in 4 bits)
    printf("After final mask: "); print_binary_uint8(x);

    return x;
}


const uint8_t h01_8 = 0x01; // 00000001 (for 8-bit, multiplication is simpler)

uint8_t popcount8c(uint8_t x) {
    printf("Initial x: "); print_binary_uint8(x);

    // --- 2-bit groups ---
    uint8_t temp = x >> 1;
    printf("After x >> 1: "); print_binary_uint8(temp);
    temp = temp & m1_8;
    printf("After (x >> 1) & m1: "); print_binary_uint8(temp);
    x = x - temp;
    printf("After x -= (x >> 1) & m1: "); print_binary_uint8(x);

    // --- 4-bit groups ---
    temp = x & m2_8;
    printf("After x & m2: "); print_binary_uint8(temp);
    uint8_t temp2 = x >> 2;
    printf("After x >> 2: "); print_binary_uint8(temp2);
    temp2 = temp2 & m2_8;
    printf("After (x >> 2) & m2: "); print_binary_uint8(temp2);
    x = temp + temp2;
    printf("After 4-bit count: "); print_binary_uint8(x);

    // --- 8-bit groups ---
    temp = x >> 4;
    printf("After x >> 4: "); print_binary_uint8(temp);
    temp = x + temp;
    printf("After x + (x >> 4): "); print_binary_uint8(temp);
    x = temp & m4_8;
    printf("After (x + (x >> 4)) & m4: "); print_binary_uint8(x);

    // --- Multiplication ---
    // For 8-bit, h01_8 is 0x01, so x * h01_8 is just x.
    // The original 64-bit version uses (x * h01) >> 56 to extract the top 8 bits.
    // For 8-bit, we can directly return x, as it already holds the popcount.
    printf("After multiplication (x * 0x01): "); print_binary_uint8(x);
    return x;
}

int main() {
    uint8_t test = 0xA5; // Example: 10100101 (binary)
    printf("Popcount of 0x%02X: %d\n", test, popcount8a(test));
    printf("\n");
    printf("Popcount of 0x%02X: %d\n", test, popcount8b(test));
    printf("\n");
    printf("Popcount of 0x%02X: %d\n", test, popcount8c(test));
    printf("\n");
    return 0;
}