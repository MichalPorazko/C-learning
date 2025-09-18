#include <stdio.h>


/*
in this code i m trying to understand how
smth |= smth | smth;

works
*/


int main() {
	unsigned char registerA = 0b00000000; // Initial value of registerA
	unsigned char registerB = 0b00000000; // Initial value of registerB

	// Define pin positions
	#define PIN0 0
	#define PIN1 1
	#define PIN2 2

	// Set specific bits in registerA using |=
	registerA |= (1 << PIN0) | (1 << PIN2);

	// Set all bits in registerB
	registerB = 0b11111111;

	// Print the results
	printf("registerA: 0b");
	for (int i = 7; i >= 0; i--) {
		printf("%d", (registerA >> i) & 1);
	}
	printf("\n");

	printf("registerB: 0b");
	for (int i = 7; i >= 0; i--) {
		printf("%d", (registerB >> i) & 1);
	}
	printf("\n");
	
	//print the results without the ) & 1
	printf("registerA without the ) & 1: 0b");
	for (int i = 7; i >= 0; i--) {
		printf("%d", (registerA >> i));
	}
	printf("\n");

	return 0;
}
