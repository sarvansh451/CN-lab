#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define SERVER_IP "127.0.0.1"
#define PORT 8080

int main() {
    int sockfd, n, arr[BUFFER_SIZE], odd_sum, even_sum;
    struct sockaddr_in server_addr;
    socklen_t len = sizeof(server_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(PORT);

    printf("Enter how many numbers to input an array: ");
    scanf("%d", &n);
    printf("Enter %d integers for the array: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    sendto(sockfd, &n, sizeof(n), 0, (struct sockaddr *)&server_addr, len);
    sendto(sockfd, arr, sizeof(int) * n, 0, (struct sockaddr *)&server_addr, len);

    recvfrom(sockfd, &odd_sum, sizeof(odd_sum), 0, (struct sockaddr *)&server_addr, &len);
    recvfrom(sockfd, &even_sum, sizeof(even_sum), 0, (struct sockaddr *)&server_addr, &len);

    printf("The client received from the server\n");
    printf("ODD Sum = %d\n", odd_sum);
    printf("Even Sum = %d\n", even_sum);

    close(sockfd);
    return 0;
}
