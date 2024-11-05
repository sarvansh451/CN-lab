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
    char arr[BUFFER_SIZE];
    socklen_t len = sizeof(server_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(PORT);

    printf("Enter a string of alphabets: ");
    scanf("%s", arr);

    sendto(sockfd, arr, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, len);

    recvfrom(sockfd, arr, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, &len);

    int n = strlen(arr);
    for (int i = 0; i < n / 2; i++) {
        char temp = arr[i];
        arr[i] = arr[n - i - 1];
        arr[n - i - 1] = temp;
    }

    printf("Client sorted array in descending order: %s\n", arr);

    close(sockfd);
    return 0;
}
