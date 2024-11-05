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
    int arr[BUFFER_SIZE], n, odd_sum = 0, even_sum = 0;
    socklen_t len = sizeof(client_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    recvfrom(sockfd, &n, sizeof(n), 0, (struct sockaddr *)&client_addr, &len);
    recvfrom(sockfd, arr, sizeof(int) * n, 0, (struct sockaddr *)&client_addr, &len);

    printf("The server received the array as follows:\n{ ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
        if (arr[i] % 2 == 0)
            even_sum += arr[i];
        else
            odd_sum += arr[i];
    }
    printf("}\nServer sending the result\n");

    sendto(sockfd, &odd_sum, sizeof(odd_sum), 0, (struct sockaddr *)&client_addr, len);
    sendto(sockfd, &even_sum, sizeof(even_sum), 0, (struct sockaddr *)&client_addr, len);

    close(sockfd);
    return 0;
}
