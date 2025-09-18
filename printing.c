#include <stdio.h>


void lcd_string(const char * str) {
    //The loop condition while (*str) checks if the current character is not the null terminator (\0).
    while(*str) {
        printf("%c", *str);
    }
}


int main(void) {
    char name[] = "John";
    int age = 30;

    // Printing strings using puts()
    puts("Using puts():");
    puts("My name is John and I'm 30 years old.");

    // Printing strings usingprintf()
    printf("\nUsing printf():\n");
    printf("My name is %s and I'm %d years old. \n", name, age);

    
    printf("priting using lcd_string() function: \n");
    lcd_string("My name is John and I'm 30 years old.\n");

}