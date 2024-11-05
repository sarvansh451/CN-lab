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

    memset(&sender_addr, 0, sizeof(sender_addr));
    sender_addr.sin_family = AF_INET;
    sender_addr.sin_addr.s_addr = INADDR_ANY;
    sender_addr.sin_port = htons(SENDER_PORT);
    bind(sockfd, (struct sockaddr *)&sender_addr, sizeof(sender_addr));

    memset(&receiver_addr, 0, sizeof(receiver_addr));
    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_addr.s_addr = inet_addr(RECEIVER_IP);
    receiver_addr.sin_port = htons(RECEIVER_PORT);

    while (1) {
        printf("Sender: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&receiver_addr, sizeof(receiver_addr));
        if (strcmp(buffer, "exit") == 0) break;

        int len = sizeof(receiver_addr);
        recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&receiver_addr, &len);
        buffer[strcspn(buffer, "\n")] = 0;
        printf("Receiver: %s\n", buffer);
        
        if (strcmp(buffer, "exit") == 0) break;
    }

    close(sockfd);
    return 0;
}
