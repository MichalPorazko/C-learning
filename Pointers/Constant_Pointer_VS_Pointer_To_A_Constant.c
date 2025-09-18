#include <stdio.h>

int main() {
    // this exists on a stack and we can modify things on the stack
    char a = 'a';

    /*
        we can't change the memory address
        stored by the pointer - we camt change the memory address stroed by the pointer, but 
        we can change the value what the pointer is pointing to 



    */

    char *const constant_pointer_to_a = &a; 

    *constant_pointer_to_a = 'b';
    printf("a after modification %c/n", a);

    char b = 'b';

    /*
    but this will be an error
    constant_pointer_to_a = &b;
    */

    char const *pointer_to_constant = &a;

    
}