#include <stdio.h>
#include <stdint.h>

#define ENC_A 2  // Example: encoder A connected to pin 2
#define ENC_B 3  // Example: encoder B connected to pin 3

// Function to simulate reading PIND and calculating encoder state
uint8_t calculate_encoder_state(uint8_t pind_value) {
    uint8_t encoder_state = (pind_value & ((1<<ENC_A) | (1<<ENC_B))) >> ENC_A;
    return encoder_state;
}

// Function to check if transition is clockwise
uint8_t is_clockwise_transition(uint8_t last_state, uint8_t current_state) {
    return ((last_state == 0b00 && current_state == 0b01) ||
            (last_state == 0b01 && current_state == 0b11) ||
            (last_state == 0b11 && current_state == 0b10) ||
            (last_state == 0b10 && current_state == 0b00));
}

void print_binary(uint8_t value, uint8_t bits) {
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
    }
}

int main() {
    // Test all possible PIND values for pins 2 and 3
    printf("PIND Value | Binary   | Encoder State | Is Clockwise\n");
    printf("------------------------------------------------\n");
    
    uint8_t last_state = 0;
    
    // Simulate a full clockwise rotation sequence
    uint8_t pin_sequence[] = {
        0b00000000, // both pins low (00)
        0b00001000, // ENC_B high, ENC_A low (01)
        0b00001100, // both pins high (11)
        0b00000100, // ENC_A high, ENC_B low (10)
        0b00000000  // back to start (00)
    };
    
    for (int i = 0; i < 5; i++) {
        uint8_t pind = pin_sequence[i];
        uint8_t state = calculate_encoder_state(pind);
        
        printf("0x%02X      | 0b", pind);
        print_binary(pind, 8);
        printf(" | 0b");
        print_binary(state, 2);
        printf("          | ");
        
        if (i > 0) {
            if (is_clockwise_transition(last_state, state)) {
                printf("Clockwise");
            } else {
                printf("Counter-clockwise");
            }
        } else {
            printf("Initial state");
        }
        printf("\n");
        
        last_state = state;
    }
    
    return 0;
}
