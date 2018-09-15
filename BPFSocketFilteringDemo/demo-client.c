#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){
    // open a udp socket
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int ret;
    // destination
    struct sockaddr_in dest_addr;
    memset(&dest_addr, 0, sizeof(struct sockaddr_in));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(60101);
    ret = inet_pton(AF_INET, "localhost", &dest_addr.sin_addr);
    if (ret < 0){
        perror("inet_pton failed");
        exit(EXIT_FAILURE);
    }

    // get message and send
    char msg[256];
    while(1){
        printf("> ");
        fgets(msg, 256, stdin);

        printf("entered %s\n", msg);
        if(strncmp(msg, "exit", 4) == 0){
            break;
        }

        ret = sendto(sock, msg, strlen(msg), 0, (struct sockaddr *) &dest_addr, sizeof(struct sockaddr));
        if (ret < 0){
            perror("sendto failed");
            exit(EXIT_FAILURE);
        }
    }

    close(sock);

    return 0;
}
