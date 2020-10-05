#include <sys/socket.h>
#include <stdio.h>
#include <dlfcn.h>
#include <string.h>

static int (*real_setsockopt)(int, int, int, void *, socklen_t) = NULL;

__attribute__((constructor))void init(){
    real_setsockopt = dlsym(RTLD_NEXT,"setsockopt");
}

int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen){
    printf("SETSOCKOPT: %d: level: %d %d=%d (%d)\r\n",sockfd,level,optname,*(int*)optval,optlen);
    real_setsockopt(sockfd,level,optname,&optval,optlen);

    if(level==SOL_SOCKET && optname==SO_REUSEADDR){
        int val = 1;
        real_setsockopt(sockfd,SOL_SOCKET,SO_KEEPALIVE,&val,optlen);
        return 0;
    }
    return 0 ;
}