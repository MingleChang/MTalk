//
//  main.c
//  server
//
//  Created by Mingle on 2018/2/27.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "server.h"

int kq, listenfd;
Base_socket *base_socket_list;

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
    Fd_queue_add_event(kq, connfd, SOCKET_READ | SOCKET_EXCEP);
    Base_socket_add(base_socket_list, connfd);
}

void handleRead(int fd) {
    Base_socket *read_socket = Base_socket_find(base_socket_list, fd);
    Base_socket_read(read_socket);
}

void handleWrite(int fd) {
    
}

int main(int argc, const char * argv[]) {
    char *host = NULL;
    char *serv = "8000";
    socklen_t addrlen;
    ssize_t n;
    listenfd = Tcp_listen(host, serv, &addrlen);
    Set_non_block(listenfd);
    kq = Fd_queue_init();
    Fd_queue_add_event(kq, listenfd, SOCKET_READ | SOCKET_EXCEP);
    base_socket_list = Base_socket_init(listenfd);
    signal(SIGALRM, sig_alrm);
    alarm(1);
    err_msg("server running...");
    for (;;) {
        struct kevent eventList[MAXLINE];
        n = kevent(kq, NULL, 0, eventList, MAXLINE, NULL);
        for (int i = 0; i < n; i++) {
            struct kevent event = eventList[i];
            if (event.ident == listenfd) {
                handleAccept(listenfd);
            }else if (event.filter == EVFILT_READ) {
                handleRead((int)event.ident);
            }else if (event.filter == EVFILT_WRITE) {
                handleWrite((int)event.ident);
            }
        }
    }
    
    return 0;
}
