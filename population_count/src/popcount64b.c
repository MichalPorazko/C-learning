#include <stdio.h>
#include <stdint.h>
#include "constants.h"
#include "print_binary.h"
#include "popcount64b.h"


int popcount64b(uint64_t x)
{
    printf("Initial x: "); print_binary(x);

    // --- 2-bit groups ---
    uint64_t temp = x >> 1;
    printf("After x >> 1: "); print_binary(temp);
    temp = temp & m1;
    printf("After (x >> 1) & m1: "); print_binary(temp);
    x = x - temp;
    printf("After x -= (x >> 1) & m1: "); print_binary(x);

    // --- 4-bit groups ---
    temp = x & m2;
    printf("After x & m2: "); print_binary(temp);
    uint64_t temp2 = x >> 2;
    printf("After x >> 2: "); print_binary(temp2);
    temp2 = temp2 & m2;
    printf("After (x >> 2) & m2: "); print_binary(temp2);
    x = temp + temp2;
    printf("After 4-bit count: "); print_binary(x);

    // --- 8-bit groups ---
    temp = x >> 4;
    printf("After x >> 4: "); print_binary(temp);
    temp = x + temp;
    printf("After x + (x >> 4): "); print_binary(temp);
    x = temp & m4;
    printf("After (x + (x >> 4)) & m4: "); print_binary(x);

    // --- Folding ---
    temp = x >> 8;
    printf("After x >> 8: "); print_binary(temp);
    x = x + temp;
    printf("After x += x >> 8: "); print_binary(x);

    temp = x >> 16;
    printf("After x >> 16: "); print_binary(temp);
    x = x + temp;
    printf("After x += x >> 16: "); print_binary(x);

    temp = x >> 32;
    printf("After x >> 32: "); print_binary(temp);
    x = x + temp;
    printf("After x += x >> 32: "); print_binary(x);

    x = x & 0x7f;
    printf("After final mask: "); print_binary(x);

    return x;
}
