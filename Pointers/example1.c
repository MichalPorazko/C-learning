
#include <stdio.h>


int main(void){

    int x = 4;
    int *pX = &x;
    int **pP = &pX;
    int *y = &x;

    
    

    printf("int *pX = &x; pX is %p\n", pX);

    printf("int **pP = &pX; so we create a pointer to a pointer which is %p\n", (void*)pP);

    printf("int y = &x; so y is %p\n", (void*)y);

    
    
    int a = 4;
    int *pA = &a;
    int * b = &pA;

    printf("int *pA = &a; pA is %p\n", pA);
    printf("int * b = &pA;, so the b pointer is now pointing to the address of pointer b so the addresses will be different  %p\n", b);
    
    int * c = pA;
    printf("int * c = pA; so c is now pointing to the same address as pA which is %p\n", c);

    




}