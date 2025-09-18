---
type: Page
title: Why does pointer b have a different value than pointer a if they point to the same value?
description: null
icon: null
createdAt: '2025-06-02T15:38:26.656Z'
creationDate: 2025-06-02 17:38
modificationDate: 2025-06-02 17:57
tags: []
coverImage: null
---



In your code, there is a misunderstanding about how pointers work, particularly when you declare and assign the pointer `b`. Let's clarify what's happening:

### Code Explanation

1. **Pointer** `pA`:

    ```c
    int a = 4;
    int *pA = &a;
    ```

    - `pA` is a pointer to an integer, and it holds the address of the integer variable `a`. So, `pA` contains the memory address where `a` is stored.

2. **Pointer** `b`:

    ```c
    int * b = &pA;
    ```

    - Here, you are trying to assign the address of `pA` to `b`. However, `pA` is already a pointer, and `&pA` gives you the address where `pA` itself is stored, not the address of `a`.

    - The correct way to assign the value of `pA` to `b` is:

        ```c
        int *b = pA;
        ```

    - This way, `b` will have the same value as `pA`, which is the address of `a`.

### Corrected Code

Here's the corrected version of your code:

```c
#include <stdio.h>

int main(void) {
    int x = 4;
    int *pX = &x;
    int **pP = &pX;
    int *y = &x;

    printf("int *pX = &x; pX is %p\n", (void*)pX);
    printf("int **pP = &pX; so we create a pointer to a pointer which is %p\n", (void*)pP);
    printf("int *y = &x; so y is %p\n", (void*)y);

    int a = 4;
    int *pA = &a;
    int *b = pA; // Assign the value of pA to b

    printf("int *pA = &a; pA is %p\n", (void*)pA);
    printf("int *b = pA;, so the b pointer should have the same address as pA, which is %p\n", (void*)b);

    return 0;
}
```

### Explanation

- **Pointer Assignment**: When you assign `b = pA`, `b` will point to the same memory location as `pA`, which is the address of `a`.

- **Pointer to Pointer**: If you want a pointer to a pointer, you need to declare `b` as `int **b = &pA;`. In this case, `b` would hold the address of `pA`, and you would need to dereference `b` to get the value of `pA`.

By correcting the assignment of `b`, you ensure that `b` and `pA` point to the same memory location, which is the address of `a`.


