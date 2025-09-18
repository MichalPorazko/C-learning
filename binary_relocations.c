#include <stdio.h>
#include <stdint.h>

void print_binary(uint8_t value) {
	for (int i = 7; i >= 0; i--) {
		printf("%d", (value >> i) & 1);
	}
	printf("\n");
}

int main() {
	
	
	uint8_t wyraz = 0b10101100; // Example byte
	uint8_t PORTD = 0b11110000; // Initial value of PORTD

	// Extract upper 4 bits
	
	
	uint8_t gorne4 = (wyraz >> 4) & 0b00001111;
	printf("The result of operation (wyraz >> 4): ");
	print_binary(wyraz >> 4);
	
	printf("gorne4: ");
	print_binary(gorne4);
	
	uint8_t dolne4 = wyraz & 0b00001111;
	printf("dolne4 = wyraz & 0b00001111 = ");
	print_binary(wyraz & 0b00001111);
	
	
	PORTD = (PORTD & 0b11110000) | dolne4;
	printf("PORTD after lower 4 bits: ");
	print_binary(PORTD);

}
