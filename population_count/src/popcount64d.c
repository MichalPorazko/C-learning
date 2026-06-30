#include <stdio.h>
#include <stdint.h>
#include "print_binary.h"
#include "popcount64d.h"

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