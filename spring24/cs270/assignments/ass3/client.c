#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 4500
#define BUFFER_SIZE 1024
#define SERVER_IP "127.0.0.1"

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        printf("failed to create socket\n");
        exit(1);
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);    
    if(inet_pton(AF_INET, SERVER_IP, &address.sin_addr) <= 0) {
        printf("invalid address\n");
        exit(1);
    }

    printf("Connecting...\n");
    if(connect(sock, (struct sockaddr*) &address, sizeof(address)) < 0) {
        printf("connection failed\n");
        exit(1);
    }

    char exp[BUFFER_SIZE] = { 0 };
    printf("> ");
    fgets(exp, BUFFER_SIZE, stdin);
    exp[strlen(exp) - 1] = '\0';

    if(send(sock, exp, strlen(exp), 0) < 0) {
        printf("failed to send\n");
        exit(1);
    }

    char buffer[BUFFER_SIZE] = { 0 };
    read(sock, buffer, BUFFER_SIZE);

    int ans = buffer[0] * 0x1000000 + 
              buffer[1] * 0x10000 + 
              buffer[2] * 0x100 + 
              buffer[3];

    printf("Answer: %d\n", buffer[3]);

    close(sock);
}
