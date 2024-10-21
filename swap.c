#include <stdio.h>


void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main() {
    int a, b;
    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);

  
    swap(&a, &b);

    printf("The numbers after swapping are: %d %d\n", a, b);
    return 0;
}

