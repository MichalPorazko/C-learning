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
	
    printf("wyraz: ");
	print_binary(wyraz);
	uint8_t gorne4 = (wyraz >> 4) & 0b00001111;

    printf("The result of operation (wyraz << 4): ");
	print_binary(wyraz << 4);
	printf("The result of operation (wyraz >> 4): ");
	print_binary(wyraz >> 4);
	
	printf("gorne4 is : (wyraz >> 4) & 0b00001111 = ");
	print_binary(gorne4);
	
	uint8_t dolne4 = wyraz & 0b00001111;
	printf("dolne4 = wyraz & 0b00001111 = ");
	print_binary(wyraz & 0b00001111);
	
	
	PORTD = (PORTD & 0b11110000) | dolne4;
	printf("PORTD after (PORTD & 0b11110000) | dolne4; : ");
	print_binary(PORTD);
	
	uint8_t PORTA = 0b00000000;
	 
	printf("PortA before: ");
    print_binary(PORTA);
    PORTA |= (1 << 5) | (1 << 2) | (1 << 7);
    printf("PortA after the operation |= (1 << 5) | (1 << 2) | (1 << 7); :");
    print_binary(PORTA);


    uint8_t value1 = 0b00000000;
    value1 = (1 << 5) | (1 << 2) | (1 << 7);
    printf("value1 after the operation attention \n without the |= but just = (1 << 5) | (1 << 2) | (1 << 7); :");
    print_binary(value1);
    
    
    uint8_t value2 = 0b00110000;
    value2 |= (1 >> 4) | (1 << 5);
    printf("value2 after the operation |= (1 >> 4) | (1 << 5); :");
    print_binary(value2);


    uint8_t value3 = 0b00000000;
    value3 = 0b10000000 | 0b01000000 ;
    printf("The operation value3 = 0b10000000 | 0b01000000\n used for moving the cursor to the second line :");
    print_binary(value3);


	//to set as input on a DDR register
	uint8_t value4 = 0b11111111;
	value4 &= ~((1 << 5) | (1 << 4) | (1 << 3));
	printf("The operation value4 &= ~((1 << 5) | (1 << 4) | (1 << 3)); :");
	print_binary(value4); 


	uint8_t value5 = 0b00000000;
	uint8_t value6 = value5 & (1 << 3);
	printf("The operation value6 = value5 & (1 << 3); :");
	print_binary(value6);


	// Simulate a port register (like PIND)
	uint8_t simulated_PIND = 0b00000000;

	// Set PD3 (Channel A) HIGH, PD2 (Channel B) LOW
	simulated_PIND = (1 << 3); // Only PD3 is HIGH

	// Read Channel A and B using bitmasking
	uint8_t channelA = (simulated_PIND & (1 << 3)) ? 1 : 0;
	uint8_t channelB = (simulated_PIND & (1 << 2)) ? 1 : 0;

	printf("Channel A: %d, Channel B: %d\n", channelA, channelB);


	
	uint8_t value7 = 0b10001110; 
	int16_t temp1 = ((value7 << 8) | value7);
	int16_t temp2 = ((value7 << 8) | value7) >> 3;
	printf("the result of the operation ((value7 << 8) | value7) is: ");
	print_binary(temp1);
	printf("the result of the operation ((value7 << 8) | value7) >> 3; is: ");
	print_binary(temp2);




}
