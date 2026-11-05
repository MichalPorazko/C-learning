/*
 * Bitwise experiments for understanding common RTL idioms in ordinary C.
 *
 * All values are unsigned and explicitly limited to the requested width.
 * This models known 0/1 bit patterns, NOT Verilog's X/Z four-state logic.
 *
 * Build: cc -std=c11 -Wall -Wextra -Wpedantic bitwise_lab.c -o bitwise_lab
 * Run:   ./bitwise_lab --help
 */

#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint32_t width_mask(unsigned width)
{
    /* Shifting by 32 is undefined in C, so handle that width separately. */
    return width == 32 ? UINT32_MAX : (UINT32_C(1) << width) - UINT32_C(1);
}

static uint32_t parse_number(const char *text)
{
    char *end = NULL;
    if (text[0] == '\0' || text[0] == '-') {
        fprintf(stderr, "Expected a non-negative decimal or hexadecimal number: %s\n", text);
        exit(EXIT_FAILURE);
    }

    errno = 0;
    /* Decimal by default; accept an explicit 0x prefix for hexadecimal. */
    int base = text[0] == '0' && (text[1] == 'x' || text[1] == 'X') ? 16 : 10;
    unsigned long number = strtoul(text, &end, base);
    if (errno != 0 || end == text || *end != '\0' || number > UINT32_MAX) {
        fprintf(stderr, "Invalid 32-bit number: %s\n", text);
        exit(EXIT_FAILURE);
    }
    return (uint32_t)number;
}

static unsigned parse_width(int argc, char **argv, int position,
                            unsigned default_width, unsigned maximum)
{
    if (argc <= position)
        return default_width;

    uint32_t width = parse_number(argv[position]);
    if (width < 1 || width > maximum) {
        fprintf(stderr, "Width must be between 1 and %u.\n", maximum);
        exit(EXIT_FAILURE);
    }
    return (unsigned)width;
}

static void print_bits(uint32_t value, unsigned width)
{
    for (unsigned n = width; n > 0; --n) {
        putchar((value & (UINT32_C(1) << (n - 1))) ? '1' : '0');
        if (n > 1 && (n - 1) % 4 == 0)
            putchar('_');
    }
}

static void show(const char *label, uint32_t value, unsigned width)
{
    value &= width_mask(width);
    printf("%-25s ", label);
    print_bits(value, width);
    printf("  (0x%0*" PRIX32 ")\n", (int)((width + 3) / 4), value);
}

static unsigned bit_count(uint32_t value)
{
    /* Deliberately simple: count individual 1 bits rather than using a trick. */
    unsigned count = 0;
    for (unsigned bit = 0; bit < 32; ++bit)
        count += (value >> bit) & UINT32_C(1);
    return count;
}

static uint32_t binary_to_gray(uint32_t binary)
{
    return binary ^ (binary >> 1);
}

static void demonstrate_ops(uint32_t first, uint32_t second, unsigned width)
{
    uint32_t mask = width_mask(width);
    first &= mask;
    second &= mask;
    show("a", first, width);
    show("b", second, width);
    show("a & b", first & second, width);
    show("a | b", first | second, width);
    show("a ^ b", first ^ second, width);
    show("~(a ^ b) (XNOR)", ~(first ^ second), width);
    show("~a", ~first, width);
    printf("a && b (C logical AND) = %u\n",
           (unsigned)(first != 0 && second != 0));
    puts("Notice that bitwise operators preserve a vector; && returns 0 or 1.");
}

static void demonstrate_shift(uint32_t value, unsigned amount, unsigned width)
{
    uint32_t mask = width_mask(width);
    value &= mask;
    show("value", value, width);
    show("value << amount", (value << amount) & mask, width);
    show("value >> amount", value >> amount, width);
    show("(value >> n) << n", (value >> amount) << amount, width);
    puts("The final expression clears the lowest n bits (alignment down).");
}

static void demonstrate_address(uint32_t address, uint32_t base,
                                uint32_t range, unsigned width)
{
    uint32_t mask = width_mask(width);
    address &= mask;
    base &= mask;
    range &= mask;

    uint32_t difference = address ^ base;
    uint32_t xnor_bits = (~difference) & mask;
    uint32_t xnor_or_range = xnor_bits | range;
    uint32_t care_mask = (~range) & mask;
    uint32_t relevant_differences = difference & care_mask;

    puts("Wally's Range is a DON'T-CARE MASK: 1 means ignore that bit.");
    show("PhysicalAddress", address, width);
    show("Base", base, width);
    show("PhysicalAddress ~^ Base", xnor_bits, width);
    show("Range (ignored bits)", range, width);
    show("XNOR | Range", xnor_or_range, width);
    printf("Reduction AND -> Match = %u\n", (unsigned)(xnor_or_range == mask));
    puts("\nEquivalent mismatches-only interpretation:");
    show("PhysicalAddress ^ Base", difference, width);
    show("~Range (cared bits)", care_mask, width);
    show("difference & ~Range", relevant_differences, width);
    printf("No relevant differences -> Match = %u\n",
           (unsigned)(relevant_differences == 0));
}

static void demonstrate_gray(unsigned width)
{
    unsigned limit = 1u << width;  /* Width is intentionally limited to 8. */
    uint32_t previous_gray = 0;

    puts("Binary -> (Binary >> 1) -> Gray = Binary XOR shifted binary");
    puts("Adjacent Gray values differ in one bit:");
    puts(" Dec | Binary | Shifted | Gray | Changed from previous");
    for (unsigned n = 0; n < limit; ++n) {
        uint32_t gray = binary_to_gray(n);
        uint32_t changed = gray ^ previous_gray;
        printf("%4u | ", n);
        print_bits(n, width);
        printf(" | ");
        print_bits(n >> 1, width);
        printf(" | ");
        print_bits(gray, width);
        printf(" | ");
        if (n == 0) {
            puts("(first value)");
        } else {
            print_bits(changed, width);
            printf(" (%u bit changed)\n", bit_count(changed));
        }
        previous_gray = gray;
    }
}

static void demonstrate_transition(uint32_t previous, uint32_t current,
                                   unsigned width)
{
    uint32_t mask = width_mask(width);
    previous &= mask;
    current &= mask;
    uint32_t difference = previous ^ current;

    show("previous word", previous, width);
    show("current word", current, width);
    show("difference (XOR)", difference, width);
    printf("Original assertion: no change OR exactly one changed bit = %s\n\n",
           difference == 0 || bit_count(difference) == 1 ? "PASS" : "FAIL");

    puts("Unroll ZipCPU's generate loop, one k at a time:");
    for (unsigned k = 0; k < width; ++k) {
        uint32_t onehot = UINT32_C(1) << k;
        bool unchanged = (difference & onehot) == 0;
        bool only_k_changed = (difference ^ onehot) == 0;
        printf("k=%2u  (1<<k)=", k);
        print_bits(onehot, width);
        printf("  diff^(1<<k)=");
        print_bits(difference ^ onehot, width);
        printf("  unchanged=%u  only_k=%u  %s\n",
               (unsigned)unchanged, (unsigned)only_k_changed,
               unchanged || only_k_changed ? "PASS" : "FAIL");
    }
}

static int selftest(void)
{
    /* Exhaust every possible 4-bit address, base and don't-care mask. */
    for (uint32_t address = 0; address < 16; ++address)
        for (uint32_t base = 0; base < 16; ++base)
            for (uint32_t range = 0; range < 16; ++range) {
                uint32_t xnor = (~(address ^ base)) & 15;
                bool match_xnor = (xnor | range) == 15;
                bool match_xor = ((address ^ base) & ~range & 15) == 0;
                if (match_xnor != match_xor) {
                    fprintf(stderr, "Address-match equivalence failed.\n");
                    return EXIT_FAILURE;
                }
            }
    puts("PASS: 4096 masked-address comparisons");

    /* Verify adjacent binary-reflected Gray codes at widths 1 through 8. */
    for (unsigned width = 1; width <= 8; ++width) {
        unsigned limit = 1u << width;
        for (unsigned n = 1; n < limit; ++n) {
            uint32_t change = binary_to_gray(n) ^ binary_to_gray(n - 1);
            if (bit_count(change) != 1) {
                fprintf(stderr, "Gray-code transition failed.\n");
                return EXIT_FAILURE;
            }
        }
    }
    puts("PASS: all adjacent Gray-code transitions for widths 1..8");

    /* Verify the unrolled assertion against the original condition. */
    for (unsigned width = 1; width <= 6; ++width) {
        uint32_t limit = UINT32_C(1) << width;
        for (uint32_t previous = 0; previous < limit; ++previous)
            for (uint32_t current = 0; current < limit; ++current) {
                uint32_t diff = previous ^ current;
                bool original = diff == 0 || bit_count(diff) == 1;
                bool unrolled = true;
                for (unsigned k = 0; k < width; ++k) {
                    uint32_t onehot = UINT32_C(1) << k;
                    bool unchanged = (diff & onehot) == 0;
                    bool only_k_changed = (diff ^ onehot) == 0;
                    unrolled &= unchanged || only_k_changed;
                }
                if (original != unrolled) {
                    fprintf(stderr, "Unrolled assertion equivalence failed.\n");
                    return EXIT_FAILURE;
                }
            }
    }
    puts("PASS: original vs. unrolled one-bit-change assertion (widths 1..6)");
    return EXIT_SUCCESS;
}

static void usage(const char *program)
{
    printf("Usage:\n");
    printf("  %s ops        <a> <b> [width=8]\n", program);
    printf("  %s shift      <value> <amount> [width=8]\n", program);
    printf("  %s address    <address> <base> <range> [width=8]\n", program);
    printf("  %s gray       [width=4]  (maximum 8)\n", program);
    printf("  %s transition <previous> <current> [width=4]\n", program);
    printf("  %s selftest\n", program);
    puts("Numbers may be decimal (15) or hexadecimal (0x0f). Width: 1..32.");
    puts("Try: address 0xa6 0xa0 0x0f 8; gray 4; transition 0x4 0x6 4");
}

int main(int argc, char **argv)
{
    if (argc < 2 || strcmp(argv[1], "--help") == 0) {
        usage(argv[0]);
        return EXIT_SUCCESS;
    }

    if (strcmp(argv[1], "ops") == 0 && (argc == 4 || argc == 5)) {
        demonstrate_ops(parse_number(argv[2]), parse_number(argv[3]),
                        parse_width(argc, argv, 4, 8, 32));
    } else if (strcmp(argv[1], "shift") == 0 && (argc == 4 || argc == 5)) {
        uint32_t amount = parse_number(argv[3]);
        if (amount >= 32) {
            fputs("Shift amount must be 0..31 for a uint32_t.\n", stderr);
            return EXIT_FAILURE;
        }
        demonstrate_shift(parse_number(argv[2]), (unsigned)amount,
                          parse_width(argc, argv, 4, 8, 32));
    } else if (strcmp(argv[1], "address") == 0 && (argc == 5 || argc == 6)) {
        demonstrate_address(parse_number(argv[2]), parse_number(argv[3]),
                            parse_number(argv[4]),
                            parse_width(argc, argv, 5, 8, 32));
    } else if (strcmp(argv[1], "gray") == 0 && (argc == 2 || argc == 3)) {
        demonstrate_gray(parse_width(argc, argv, 2, 4, 8));
    } else if (strcmp(argv[1], "transition") == 0 && (argc == 4 || argc == 5)) {
        demonstrate_transition(parse_number(argv[2]), parse_number(argv[3]),
                               parse_width(argc, argv, 4, 4, 32));
    } else if (strcmp(argv[1], "selftest") == 0 && argc == 2) {
        return selftest();
    } else {
        usage(argv[0]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
