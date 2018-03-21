//
//  main.c
//  server
//
//  Created by Mingle on 2018/2/27.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "server.h"

int global_fq, listenfd;
struct base_socket *base_socket_list;

static void sig_alrm(int signo) {
    Base_socket_heart_beat();
    alarm(1);
}

void handleAccept(int fd) {
    int connfd = accept(fd, NULL, NULL);
    if (connfd < 0) {
        return;
    }
    Set_non_block(connfd);
    Set_no_delay(connfd);
    Fd_queue_add_event(global_fq, connfd, SOCKET_READ | SOCKET_EXCEP);
    Base_socket_add(base_socket_list, connfd);
}

void handleRead(int fd) {
    struct base_socket *read_socket = Base_socket_find(base_socket_list, fd);
    Base_socket_read(read_socket);
}

void handleWrite(int fd) {
    
}

void dispatch(int fd, uint8_t event) {
    if (fd == listenfd) {
        handleAccept(listenfd);
    }else if (event == SOCKET_READ) {
        handleRead(fd);
    }else if (event == SOCKET_WRITE) {
        handleWrite(fd);
    }
}

int main(int argc, const char * argv[]) {
    char *host = NULL;
    char *serv = "8000";
    socklen_t addrlen;
    listenfd = Tcp_listen(host, serv, &addrlen);
    Set_non_block(listenfd);
    global_fq = Fd_queue_init();
    Fd_queue_add_event(global_fq, listenfd, SOCKET_READ | SOCKET_EXCEP);
    base_socket_list = Base_socket_init(listenfd);
    signal(SIGALRM, sig_alrm);
    alarm(1);
    err_msg("server running...");
    for (;;) {
        Fd_queue_dispatch(global_fq, dispatch);
    }
    
    return 0;
}
