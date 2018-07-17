#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int sock, fd, str_len, i, pid;
    struct sockaddr_in addr, addr2;
    char buf[100];

    fd = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(7777);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int addr_size = sizeof(addr);
    bind(fd, (struct sockaddr *)&addr, addr_size);

    listen(fd, 5);

    while(1) {
        sock = accept(fd, (struct sockaddr *)&addr,  &addr_size);
        recv(sock, buf, 100, 0);
        pid = fork();
        if(pid == 0){
            printf("sock opened");
            int sock2, sock3;
            sock2 = socket(AF_INET, SOCK_STREAM, 0);
            addr2.sin_family = AF_INET;
            addr2.sin_port = htons(7777);
            addr2.sin_addr.s_addr = htonl(INADDR_ANY);
            bind(sock2, (struct sockaddr *)&addr, sizeof(addr2));
            sock = accept(sock3, (struct sockaddr *)&addr,  &addr_size);
            send(sock3, &addr2, sizeof(addr2), 0);
            recv(sock3, buf, 100, 0);
            sleep(15);
            close(sock3);
        }

        close(sock);
    }

    return 0;
}