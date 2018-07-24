#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    struct sockaddr_in server;
    socklen_t length = sizeof(struct sockaddr_in);
    int serv_sd;
    char msg[100];

    if ((serv_sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        perror("Socket create error");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    server.sin_port = htons(8888);

    if (connect(serv_sd, &server, length) < 0) {
        perror("Connect error");
        exit(2);
    }

    while (1) {

        if (!scanf("%s", msg)) {
            printf("Scanf error\n");
            exit(3);
        }

        if (send(serv_sd, msg, 100, 0) < 0) {
            perror("Send error");
            exit(4);
        }
        printf("%s\n", msg);

        if (recv(serv_sd, msg, 100, 0) < 0) {
            perror("Recv error");
            exit(5);
        }
    }

    return 0;
}