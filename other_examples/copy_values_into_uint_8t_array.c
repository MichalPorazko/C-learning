#include <stdio.h>
#include <string.h>
#include <stdint.h>




uint8_t* pack_data(float float_val, const char* char_array, uint8_t bit_values, uint16_t* size) {

    uint16_t total_size = sizeof(float) + strlen(char_array) + 1 + sizeof(bit_values);
    uint8_t* packed_data = (uint8_t*)malloc(total_size);

    if (packed_data == NULL) {
        *size = 0;
        return NULL;
    }

    // to keep track of the current position in the array
    uint16_t offset = 0;

    memcpy(packed_data + offset, &float_val, sizeof(float));
    offset += sizeof(float);

    /*
        using the memcpy will copy '\0' character into the array
    */
    strcpy((char*)(packed_data + offset), char_array);
    offset += strlen(char_array) + 1; 

    // Pack the bit values into the array
    memcpy(packed_data + offset, &bit_values, sizeof(bit_values));
    offset += sizeof(bit_values);

    *size = offset;

    return packed_data;
}

int main() {
    float float_val = 3.14f;
    const char* char_array = "Hello";
    uint8_t bit_values = 0x55; //  01010101

    uint16_t size;
    uint8_t* packed_data = pack_data(float_val, char_array, bit_values, &size);

    if (packed_data != NULL) {
        

        printf("Packed data: ");
        for (uint16_t i = 0; i < size; i++) {
            printf("%02X ", packed_data[i]);
        }
        printf("\n");

        free(packed_data); 
        
    }

    return 0;
}
