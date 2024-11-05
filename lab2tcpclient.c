#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <Server IP> <Port>\n", argv[0]);
        return 1;
    }

    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));

    connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    while (1) {
        printf("Client: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        send(sockfd, buffer, strlen(buffer), 0);

        if (strcmp(buffer, "close\n") == 0) break;

        int bytes = recv(sockfd, buffer, BUFFER_SIZE, 0);
        buffer[bytes] = '\0';
        printf("Server: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}
