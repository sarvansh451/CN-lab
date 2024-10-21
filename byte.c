#include <stdio.h>

int main() {
    int num = 0x12345678; 

   
    unsigned char byte1 = (unsigned char)(num & 0xFF);          
    unsigned char byte2 = (unsigned char)((num >> 8) & 0xFF);   
    unsigned char byte3 = (unsigned char)((num >> 16) & 0xFF);  
    unsigned char byte4 = (unsigned char)((num >> 24) & 0xFF);  


    printf("Byte 1: 0x%02X\n", byte1);
    printf("Byte 2: 0x%02X\n", byte2);
    printf("Byte 3: 0x%02X\n", byte3);
    printf("Byte 4: 0x%02X\n", byte4);

    return 0;
}

