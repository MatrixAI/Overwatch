#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/filter.h>
#include <unistd.h>
#include <arpa/inet.h>

struct sock_filter code[] = {
    { BPF_LD | BPF_H | BPF_ABS, 0, 0, 12 }, // grab ethertype
    { BPF_JMP | BPF_JEQ, 0, 1, 0x800 },     // check ipv4
    { BPF_LD | BPF_B | BPF_ABS, 0, 0, 23},  // grab protocol
    { BPF_JMP | BPF_JEQ, 0, 1, 0x11 },      // check udp
    { BPF_RET, 0, 0, -1 },
    { BPF_RET, 0, 0, 0},
};

struct sock_fprog bpf = {
    .len = 6, .filter = code,
};

int main(){
    // open a udp socket
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    int ret;

    // bind addr
    struct sockaddr_in bind_addr;
    memset(&bind_addr, 0, sizeof(struct sockaddr_in));
    bind_addr.sin_family = AF_INET;
    bind_addr.sin_port = htons(60101);
    ret = inet_pton(AF_INET, "localhost", &bind_addr.sin_addr);
    if (ret < 0){
        perror("inet_pton failed");
        exit(EXIT_FAILURE);
    }

    ret = bind(sock, (struct sockaddr*) &bind_addr, sizeof(struct sockaddr));
    if(ret < 0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // get message and send
    char msg[256];
    int len = 0;
    while(1){
        puts("Listening ... ");

        ret = recv(sock, msg, 256, 0);
        if (ret < 0){
            perror("recv failed");
            exit(EXIT_FAILURE);
        }

        printf("Message received: %s\n", msg);

        // blocks future data transfer if "block" received
        if(strncmp("block", msg, 5) == 0){
            puts("Blocking future data transfer.");
            ret = setsockopt(sock, SOL_SOCKET, SO_ATTACH_FILTER, &bpf, sizeof(bpf));
            if (ret < 0){
                perror("setsockopt failed");
                exit(EXIT_FAILURE);
            }
        }
    }

    close(sock);

    return 0;
}
