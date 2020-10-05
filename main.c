#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

int main() {
    struct sockaddr_in serv_addr;
    int listen_fd = 0;
    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        exit(1);
    }
    bzero(&serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(8080);

    if (bind(listen_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
        exit(1);
    }
    
    // 设置 backlog 为 1
    if (listen(listen_fd, 1) == -1) {
           exit(1);
     }
    sleep(100000000);
    return 0;
}
