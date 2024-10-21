#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <IP Address> <Port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));
    
    
    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    
    int 
    
    printf("Connected to server at %s:%s\n", argv[1], argv[2]);
    
  
    while (1) {
        printf("Client: ");
        fgets(buffer, 1024, stdin);
        send(sock, buffer, strlen(buffer), 0);
        
        if (strncmp(buffer, "close", 5) == 0) {
            printf("Closing connection...\n");
            break;
        }

        memset(buffer, 0, sizeof(buffer));
        read(sock, buffer, 1024);
        printf("Server: %s\n", buffer);
    }

    close(sock);
    return 0;
}

