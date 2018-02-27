//
//  main.c
//  server
//
//  Created by Mingle on 2018/2/27.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "server.h"

int kq, listenfd;

int main(int argc, const char * argv[]) {
    char *host = NULL;
    char *serv = "8000";
    socklen_t addrlen;
    ssize_t n;
    listenfd = Tcp_listen(host, serv, &addrlen);
    Set_non_block(listenfd);
    kq = Fd_queue_init();
    Fd_queue_add_event(kq, listenfd, SOCKET_READ | SOCKET_EXCEP);
    int fd[10] = {-1};
    for (;;) {
        struct kevent eventList[MAXLINE];
        n = kevent(kq, NULL, 0, eventList, MAXLINE, NULL);
        for (int i = 0; i < n; i++) {
            struct kevent event = eventList[i];
            if (event.ident == listenfd) {
                int connfd = accept(listenfd, NULL, NULL);
                for (int i = 0 ; i < 10; i++) {
                    if (fd[i] <= 0) {
                        fd[i] = connfd;
                        break;
                    }
                }
                Set_non_block(connfd);
                Fd_queue_add_event(kq, connfd, SOCKET_READ | SOCKET_EXCEP);
            }else if (event.filter == EVFILT_READ) {
                char buff[MAXLINE];
                int connfd = (int)event.ident;
                n = read(connfd, buff, (size_t)MAXLINE);
                if (n <= 0) {
                    for (int i = 0 ; i < 10; i++) {
                        if (fd[i] == connfd) {
                            fd[i] = 0;
                        }
                    }
                    Fd_queue_delete_event(kq, connfd, SOCKET_READ | SOCKET_EXCEP);
                    close(connfd);
                }
                for (int i = 0 ; i < 10; i++) {
                    if (fd[i] > 0) {
                        write(fd[i], buff, n);
                    }
                }
            }else if (event.filter == EVFILT_WRITE) {
                printf("write");
            }
        }
    }
    
    return 0;
}
