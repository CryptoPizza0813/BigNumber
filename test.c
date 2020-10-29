#include <stdio.h>

int main() 
{
    int A[3] = {0, 3, 6};

    int* a = A;

    int value = *(a + 2);

    printf("%d\n", value);

    return 0;
}