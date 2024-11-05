#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define SERVER_IP "127.0.0.1"
#define PORT 8080

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char expr[BUFFER_SIZE];
    socklen_t len = sizeof(server_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(PORT);

    printf("Enter an expression (e.g., 4 + 5): ");
    fgets(expr, BUFFER_SIZE, stdin);

    sendto(sockfd, expr, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, len);

    recvfrom(sockfd, expr, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, &len);
    printf("Server result: %s\n", expr);

    close(sockfd);
    return 0;
}
