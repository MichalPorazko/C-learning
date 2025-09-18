#include <stdio.h>

int main(void) {

    // this exists on a stack and we can modify things on the stack
    char s1[] = "Hello, World!";

    s1[0] = 'A';

    printf("s1 after modification: %s\n", s1);

    char *s2 = "Michał";
    printf("s2 %s\n", s2);

    s2++;
    printf("s2++ after increment: %s\n", s2);

    //this is illegal

    
}