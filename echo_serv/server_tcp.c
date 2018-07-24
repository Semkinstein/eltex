#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    struct sockaddr_in client, server;
    socklen_t length = sizeof(struct sockaddr_in);
    int serv_sd, cl_sd;
    char msg[100];

    if ((serv_sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        perror("Socket create error");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    server.sin_port = htons(8888);

    if (bind(serv_sd, &server, sizeof(struct sockaddr_in)) < 0) {
        perror("Bind error");
        exit(2);
    }

    listen(serv_sd, 5);
    if ((cl_sd = accept(serv_sd, &client, &length)) < 0) {
        perror("Accept error");
        exit(5);
    }

    while (1) {
        switch (recv(cl_sd, msg, 100, 0)) {
            case -1: {
                perror("Recv error");
                exit(3);
                break;
            }
            case 0: {
                perror("Socket closed");
                exit(0);
                break;
            }
            default: {
                printf("%s\n", msg);
            }
        }

        strcat(msg, "?");
        if (send(cl_sd, msg, 100, 0) < 0) {
            perror("Send error");
            exit(4);
        }
    }

    return 0;
}