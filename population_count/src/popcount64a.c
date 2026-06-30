#include <stdio.h>
#include <stdint.h>
#include "constants.h"
#include "print_binary.h"
#include "popcount64a.h"

int popcount64a(uint64_t x)
{
    printf("Initial x: "); print_binary(x);

    // --- 2-bit groups ---
    uint64_t temp = x & m1;
    printf("After x & m1: "); print_binary(temp);
    temp = x >> 1;
    printf("After x >> 1: "); print_binary(temp);
    temp = temp & m1;
    printf("After (x >> 1) & m1: "); print_binary(temp);
    x = (x & m1) + temp;
    printf("After 2-bit count: "); print_binary(x);

    // --- 4-bit groups ---
    temp = x & m2;
    printf("After x & m2: "); print_binary(temp);
    temp = x >> 2;
    printf("After x >> 2: "); print_binary(temp);
    temp = temp & m2;
    printf("After (x >> 2) & m2: "); print_binary(temp);
    x = (x & m2) + temp;
    printf("After 4-bit count: "); print_binary(x);

    // --- 8-bit groups ---
    temp = x & m4;
    printf("After x & m4: "); print_binary(temp);
    temp = x >> 4;
    printf("After x >> 4: "); print_binary(temp);
    temp = temp & m4;
    printf("After (x >> 4) & m4: "); print_binary(temp);
    x = (x & m4) + temp;
    printf("After 8-bit count: "); print_binary(x);

    // --- 16-bit groups ---
    temp = x & m8;
    printf("After x & m8: "); print_binary(temp);
    temp = x >> 8;
    printf("After x >> 8: "); print_binary(temp);
    temp = temp & m8;
    printf("After (x >> 8) & m8: "); print_binary(temp);
    x = (x & m8) + temp;
    printf("After 16-bit count: "); print_binary(x);

    // --- 32-bit groups ---
    temp = x & m16;
    printf("After x & m16: "); print_binary(temp);
    temp = x >> 16;
    printf("After x >> 16: "); print_binary(temp);
    temp = temp & m16;
    printf("After (x >> 16) & m16: "); print_binary(temp);
    x = (x & m16) + temp;
    printf("After 32-bit count: "); print_binary(x);

    // --- 64-bit groups ---
    temp = x & m32;
    printf("After x & m32: "); print_binary(temp);
    temp = x >> 32;
    printf("After x >> 32: "); print_binary(temp);
    temp = temp & m32;
    printf("After (x >> 32) & m32: "); print_binary(temp);
    x = (x & m32) + temp;
    printf("After 64-bit count: "); print_binary(x);

    return x;
}
