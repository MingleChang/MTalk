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
    for (;;) {
        struct kevent eventList[MAXLINE];
        n = kevent(kq, NULL, 0, eventList, MAXLINE, NULL);
        for (int i = 0; i < n; i++) {
            struct kevent event = eventList[i];
            if (event.ident == listenfd) {
                int connfd = accept(listenfd, NULL, NULL);
                Set_non_block(connfd);
                Fd_queue_add_event(kq, connfd, SOCKET_READ | SOCKET_EXCEP);
                Base_socket_add(base_socket_list, connfd);
            }else if (event.filter == EVFILT_READ) {
                char buff[MAXLINE];
                int connfd = (int)event.ident;
                n = read(connfd, buff, (size_t)MAXLINE);
                if (n <= 0) {
                    Base_socket_remove(base_socket_list, connfd);
                    Fd_queue_delete_event(kq, connfd, SOCKET_READ | SOCKET_EXCEP);
                    close(connfd);
                }
                Base_socket *con_socket = base_socket_list->next;
                while (con_socket != NULL) {
                    write(con_socket->fd, buff, n);
                    con_socket = con_socket->next;
                }
            }else if (event.filter == EVFILT_WRITE) {
                printf("write");
            }
        }
    }
    
    return 0;
}
