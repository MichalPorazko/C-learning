/*#include <stdio.h>
#include <stdint.h>
#include "popcount64a.h"
#include "popcount64b.h"
#include "popcount64c.h"
#include "popcount64d.h"

int main() {
    uint64_t test = 0x123456789ABCDEF0;
    printf("Popcount: %d\n", popcount64a(test));
    printf("\n");
    printf("Popcount: %d\n", popcount64b(test));
    printf("\n");
    printf("Popcount: %d\n", popcount64c(test));
    printf("\n");
    printf("Popcount: %d\n", popcount64d(test));
    printf("\n");
    return 0;
}*/

/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdint.h>

const uint64_t m1  = 0x5555555555555555; //binary: 0101...
const uint64_t m2  = 0x3333333333333333; //binary: 00110011..
const uint64_t m4  = 0x0f0f0f0f0f0f0f0f; //binary:  4 zeros,  4 ones ...
const uint64_t m8  = 0x00ff00ff00ff00ff; //binary:  8 zeros,  8 ones ...
const uint64_t m16 = 0x0000ffff0000ffff; //binary: 16 zeros, 16 ones ...
const uint64_t m32 = 0x00000000ffffffff; //binary: 32 zeros, 32 ones
const uint64_t h01 = 0x0101010101010101; //the sum of 256 to the power of 0,1,2,3...

void print_binary(uint64_t x) {
    for (int i = 63; i >= 0; i--) {
        putchar((x & (1ULL << i)) ? '1' : '0');
    }
    putchar('\n');
}


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
int popcount64c(uint64_t x)
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

    // --- Multiplication ---
    temp = x * h01;
    printf("After x * h01: "); print_binary(temp);
    x = temp >> 56;
    printf("After (x * h01) >> 56: "); print_binary(x);

    return x;
}
int popcount64d(uint64_t x)
{
    int count = 0;
    printf("Initial x: "); print_binary(x);

    while (x) {
        uint64_t temp = x - 1;
        printf("After x - 1: "); print_binary(temp);
        x = x & temp;
        printf("After x &= x - 1: "); print_binary(x);
        count++;
        printf("Count: %d\n", count);
    }

    return count;
}

int main() {
    uint64_t test = 0x123456789ABCDEF0;
    printf("Popcount: %d\n", popcount64a(test));
    printf("\n");
    printf("Popcount: %d\n", popcount64b(test));
    printf("\n");
    printf("Popcount: %d\n", popcount64c(test));
    printf("\n");
    printf("Popcount: %d\n", popcount64d(test));
    printf("\n");
    return 0;
}