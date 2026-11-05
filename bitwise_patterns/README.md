# Bitwise patterns: an RTL learner's C playground

This little C11 program traces intermediate **bit patterns** in examples from
SystemVerilog RTL. It uses plain `uint32_t` so you can edit one value at a time,
compile quickly, and see the result printed as binary.

Existing related examples in this repository: `../binary_relocations.c`,
`../encoder_binary_moving.c`, and `../population_count/`.

## Build and run

From the `bitwise_patterns/` directory:

```sh
cc -std=c11 -Wall -Wextra -Wpedantic -O2 bitwise_lab.c -o bitwise_lab
./bitwise_lab --help
./bitwise_lab selftest
```

Try these four investigations:

```sh
# XNOR, range mask, reduction AND, and an equivalent XOR comparison
./bitwise_lab address 0xa6 0xa0 0x0f 8

# Explore every 4-bit binary value, its shifted copy, and the Gray code
./bitwise_lab gray 4

# A one-bit change between 0100 and 0110: passes ZipCPU's assertion
./bitwise_lab transition 0x4 0x6 4

# A two-bit change between 0100 and 0111: fails the assertion
./bitwise_lab transition 0x4 0x7 4

# General bitwise operations and an alignment-by-shifting example
./bitwise_lab ops 0x04 0x02 4
./bitwise_lab shift 0x2f 2 8
```

Numbers are decimal by default or hexadecimal with `0x`. The optional width
is 1 to 32 bits (the Gray-code table is capped at 8 bits to keep it readable).

## What to notice

### 1. A range mask is not a numeric comparison

Wally's address decoder uses:

```systemverilog
assign Match = &((PhysicalAddress ~^ Base) | Range);
```

`Range` is a **don't-care mask**: a `1` marks an address bit that does not
need to equal `Base`. For `Base = 0xA0`, `Range = 0x0F`, the top nibble must be
`1010` but the bottom nibble can vary: `0xA0` through `0xAF` match.

Run `address 0xa6 0xa0 0x0f 8` and inspect **each** intermediate value. Then
change only the range to `0xf0`. Which bits must now match?

The equivalent known-bit formula is:

```systemverilog
((PhysicalAddress ^ Base) & ~Range) == 0
```

### 2. Gray code compares neighboring binary bits

```systemverilog
assign graycounter = counter ^ (counter >> 1);
```

The top Gray bit equals the top binary bit. Each lower Gray bit is the XOR
of its binary bit and the adjacent higher binary bit:

```text
g[3] = b[3]
g[2] = b[3] ^ b[2]
g[1] = b[2] ^ b[1]
g[0] = b[1] ^ b[0]
```

When a binary counter increments, a run of trailing 1s flips to zeros while
the next zero becomes one. The XOR between neighboring positions changes
at just one boundary. Explore `gray 4`, especially binary 7 -> 8.

### 3. XOR difference against `1 << k` checks **exactly that bit**

Let `difference = current ^ previous`. The expression

```systemverilog
(difference ^ (1 << k)) == 0
```

means `difference == (1 << k)`: no bit changed except `k`, and bit `k`
did change. In ZipCPU's generated assertion, each bit position either
remains unchanged or must be the *only* changed bit. Run both `transition`
examples and compare each iteration of `k`.

## Important differences from SystemVerilog

- C has only binary integer values here: no Verilog `X` or `Z` states.
- C integer promotions and expression widths differ from SystemVerilog.
- This program explicitly masks results to a selected width. In actual RTL,
  always check widths, signedness, and context, especially around `~` and shifts.
- Shifting a 32-bit C integer by 32 or more is undefined behavior; the `shift`
  command therefore rejects shift amounts above 31.
- This program helps you understand the *mathematics* of the operations; use
  Icarus Verilog or Verilator to confirm actual SystemVerilog syntax and behavior.
- Passing Gray codes through clock domains still requires correct synchronizers
  and timing constraints. Gray coding does not eliminate metastability.

## Suggested learning sequence

1. Predict the printed value **before** running the command.
2. Change one input bit and check how every intermediate pattern changes.
3. Rewrite the expression in a second equivalent form.
4. Use `./bitwise_lab selftest` to check the relevant identities exhaustively
   over small widths.
5. Port the expression back to SystemVerilog and inspect a waveform or use an
   assertion. Later, formal equivalence and Yosys synthesis can tell you whether
   two implementations are functionally equivalent and how they map to logic.

Sources: [Wally address decoder](https://github.com/openhwfoundation/cvw/blob/f08efddefcb5cc3cd2fe8faec7502417a4a05680/src/mmu/adrdec.sv),
[ZipCPU asynchronous FIFO](https://zipcpu.com/blog/2018/07/06/afifo.html).
