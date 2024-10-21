#include <stdio.h>


int multiply(int x, int y) {
   
    if (x == 0 || y == 0) {
        return 0;
    }
    if (y == 1) {
        return x;
    }
    int half = y / 2;
    int product1 = multiply(x, half);
    int product2 = multiply(x, y - half);

    return product1 + product2;
}

int main() {
    int a, b;
    printf("Enter two numbers to multiply: ");
    scanf("%d %d", &a, &b);
    int result = multiply(a, b);
    printf("Product of %d and %d is: %d\n", a, b, result);

    return 0;
}

