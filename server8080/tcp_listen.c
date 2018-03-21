//
//  tcp_listen_noblock.c
//  server
//
//  Created by Mingle on 2018/2/27.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "server.h"

int tcp_listen(const char *host, const char *serv, socklen_t *addrlenp) {
    int fd, n;
    const int on = 1;
    Addrinfo hints, *res, *ressave;
    
    bzero(&hints, sizeof(Addrinfo));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    
    if ((n = getaddrinfo(host, serv, &hints, &res)) != 0) {
        err_quit("tcp_connect error for %s, %s: %s", host, serv, gai_strerror(n));
    }
    ressave = res;
    do {
        fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (fd < 0) {
            continue;
        }
        setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
        if (bind(fd, res->ai_addr, res->ai_addrlen) == 0) {
            break;
        }
        close(fd);
    } while ((res = res->ai_next) != NULL);
    if (res == NULL) {
        err_sys("tcp_connect error for %s, %s", host, serv);
    }
    listen(fd, LISTENQ);
    
    return fd;
}

int Tcp_listen(const char *host, const char *serv, socklen_t *addrlenp) {
    return tcp_listen(host, serv, addrlenp);
}
