#include <stdio.h>
#include <stdint.h>

void print_binary(uint64_t x) {
    for (int i = 63; i >= 0; i--) {
        putchar((x & (1ULL << i)) ? '1' : '0');
    }
    putchar('\n');
}
