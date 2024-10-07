#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#define PORT 4500
#define STACK_SIZE 1024
#define BUFFER_SIZE 1024

int stack[STACK_SIZE];
int head = -1;

void push(int n) {
    stack[++head] = n;
}

int pop() {
    return stack[head--];
}

int calc(int n1, int n2, char op) {
    switch (op) {
        case '+':
            return n1 + n2;
        case '-':
            return n1 - n2;
        case '*':
            return n1 * n2;
        case '/':
            return n1 / n2;
        case '%':
            return n1 % n2;
    }
}

int evaluate(char* exp) {
    int len = strlen(exp);
    for(int i = 0; i < len; i++) {
        if(exp[i] == ' ') continue;
        if(isdigit(exp[i])) {
            int n = 0;
            while(isdigit(exp[i])) {
                n *= 10;
                n += exp[i] - '0';
                i++;
            }
            push(n);
        }
        else {
            int n2 = pop();
            int n1 = pop();
            push(calc(n1, n2, exp[i]));
        }
    }
    return pop();
}

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == 0) {
        printf("failed to create socket\n");
        exit(1);
    }
    printf("socket created\n");

    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int opt = 1;
    if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
        printf("socket options failure %s\n", strerror(errno));
        exit(0);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);    
    printf("socket initialized\n");

    if(bind(sock, (struct sockaddr*) &address, sizeof(address)) < 0) {
        printf("failed to bind");
        exit(1);
    }
    printf("binded\n");

    if(listen(sock, 3) < 0) {
        printf("listen failed\n");
        exit(1);
    }
    printf("listening\n");

    int newsock = accept(sock, (struct sockaddr*) &address, (socklen_t*) &addrlen);
    if(newsock < 0) {
        printf("failed to create read socket\n");
        exit(1);
    }
    printf("created read socket\n");

    char exp[BUFFER_SIZE] = { 0 };
    read(newsock, exp, BUFFER_SIZE);
    printf("read expression: %s\n", exp);

    int ans = evaluate(exp);

    char output[BUFFER_SIZE];
    output[0] = (ans >> 24) & 0xFF;
    output[1] = (ans >> 16) & 0xFF;
    output[2] = (ans >> 8) & 0xFF;
    output[3] = ans & 0xFF;

    send(newsock, output, BUFFER_SIZE, 0);
    printf("sent answer: %d\n", ans);

    close(sock);
    close(newsock);
}