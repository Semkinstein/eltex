#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    int sock, str_len;
    struct sockaddr_in addr;
    char buf[100]= "test";

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(7777);
    //addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    int addr_size = sizeof(addr);
    if(connect(sock, (struct sockaddr *)&addr, addr_size) < 0)
    {
        perror("connect");
        exit(2);
    }
    while(1) {
        send(sock, buf, sizeof(buf), 0);
        recv(sock, &addr, sizeof(addr), 0);
        send(sock, buf, sizeof(buf), 0);
        close(sock);
    }

    return 0;
}
