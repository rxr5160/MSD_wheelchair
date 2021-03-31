#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define IP_ADDR "129.21.119.148"
#define PORT 1234

bool g_running = true;

void handle_signal(int sig){
    g_running = false;
}

int main(){

    int socklen = 0;
    int client, server;
    struct sockaddr_in addr = {0};

    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr(IP_ADDR);
    fprintf(stdout, "IP Addr %s\n", IP_ADDR);

    signal(SIGINT, handle_signal);

    server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(-1 == server){
        fprintf(stdout, "Failed to create server socket\n");
        return 1;
    }
    fprintf(stdout, "Server socket created\n");

    if(-1 == bind(server, (struct sockaddr*)&addr, sizeof(addr))){
        fprintf(stdout, "Failed to bind\n");
        fprintf(stderr, "Errno of %d, %s\n", errno, strerror(errno));
        return 1;
    }
    fprintf(stdout, "Bind complete\n");

    if(-1 == listen(server, 2)){
        fprintf(stdout, "Failed listen\n");
        return 1;
    }
    fprintf(stdout, "Listening...\n");

    socklen = sizeof(addr);
    while(g_running){
        client = accept(server, (struct sockaddr*)&addr, &socklen);
        if(client < 0){
            break;
        }
        char buffer[10];
        ssize_t numBytesRcvd = recv(client, buffer, 10, 0);
        fprintf(stdout, "Message from Client %s", buffer);
        fprintf(stdout, "Client accepted with fd = %d\n", client);
    }
    close(server);
    return 0;
}
