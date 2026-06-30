#include <stdio.h>
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
}