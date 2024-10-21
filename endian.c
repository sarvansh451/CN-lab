#include <stdio.h>

// Function to check endianness
void check_endianness() {
    unsigned int i = 1;        // Initialize an unsigned integer with the value 1
    char *c = (char*)&i;       // Cast the address of the integer to a pointer to char

    if (*c)                    
        printf("The host machine is Little Endian.\n"); // If the first byte is non-zero, the system is Little Endian
    else
        printf("The host machine is Big Endian.\n");    // If the first byte is zero, the system is Big Endian
}

// Function to print bytes of a number
void print_bytes(int num) {
    unsigned char *p = (unsigned char *)&num;
    printf("Byte 1: 0x%02X\n", p[0]);
    printf("Byte 2: 0x%02X\n", p[1]);
    printf("Byte 3: 0x%02X\n", p[2]);
    printf("Byte 4: 0x%02X\n", p[3]);
}

// Function to convert between Little Endian and Big Endian
int convert_endianness(int num) {
    return ((num >> 24) & 0x000000FF) |
           ((num >> 8) & 0x0000FF00) |
           ((num << 8) & 0x00FF0000) |
           ((num << 24) & 0xFF000000);
}

int main() {
    int num;

    // Check endianness
    check_endianness();

    // Enter a number
    printf("Enter a number (in hex, e.g., 0x12345678): ");
    scanf("%x", &num);

    // Print original bytes
    printf("Original number bytes:\n");
    print_bytes(num);

    // Convert endianness and print
    int converted_num = convert_endianness(num);
    printf("Converted number bytes:\n");
    print_bytes(converted_num);
    printf("Original number: 0x%08X\n", num);
    printf("Converted number: 0x%08X\n", converted_num);

    return 0;
}

