#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define RECEIVER_IP "127.0.0.1"
#define RECEIVER_PORT 8080
#define SENDER_PORT 8081

int main() {
    int sockfd;
    struct sockaddr_in receiver_addr, sender_addr;
    char buffer[BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&receiver_addr, 0, sizeof(receiver_addr));
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_addr.s_addr = inet_addr(RECEIVER_IP);
    receiver_addr.sin_port = htons(RECEIVER_PORT);
    bind(sockfd, (struct sockaddr *)&receiver_addr, sizeof(receiver_addr));

    while (1) {
        int len = sizeof(sender_addr);
        recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&sender_addr, &len);
        buffer[strcspn(buffer, "\n")] = 0;
        printf("Sender: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0) break;

        printf("Receiver: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&sender_addr, len);
        if (strcmp(buffer, "exit") == 0) break;
    }

    close(sockfd);
    return 0;
}
