//
//  server.h
//  server
//
//  Created by Mingle on 2018/2/27.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#ifndef server_h
#define server_h

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <net/if.h>
#include <netdb.h>
#include <stdarg.h>
#include <string.h>
#include <sys/event.h>
#include <sys/errno.h>
#include <fcntl.h>
#include <uuid/uuid.h>
#include "base_socket.h"

#define LISTENQ 1024
#define MAXLINE 4096

extern int kq, listenfd;
extern Base_socket *base_socket_list;

typedef struct addrinfo Addrinfo;
typedef struct timespec Timespec;

enum {
    SOCKET_READ  = 1,
    SOCKET_WRITE = 1<<1,
    SOCKET_EXCEP = 1<<2,
    SOCKET_ALL   = (SOCKET_READ | SOCKET_WRITE | SOCKET_EXCEP)
};

int Tcp_listen(const char *host, const char *serv, socklen_t *addrlenp);

void Set_non_block(int fd);

int Fd_queue_init(void);
void Fd_queue_add_event(int fq, int fd, uint8_t event);
void Fd_queue_delete_event(int fq, int fd, uint8_t event);

void err_dump(const char *, ...);
void err_msg(const char *, ...);
void err_quit(const char *, ...);
void err_ret(const char *, ...);
void err_sys(const char *, ...);

#endif /* server_h */
