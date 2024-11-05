#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define PORT 8080

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char expr[BUFFER_SIZE];
    socklen_t len = sizeof(client_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    recvfrom(sockfd, expr, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &len);

    int a, b;
    char op;
    sscanf(expr, "%d %c %d", &a, &op, &b);
    int result;
    switch (op) {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/': result = b != 0 ? a / b : 0; break;
        default: result = 0; break;
    }

    sprintf(expr, "%d", result);
    sendto(sockfd, expr, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, len);

    close(sockfd);
    return 0;
}
