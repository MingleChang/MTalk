//
//  client.h
//  test
//
//  Created by Mingle on 2018/3/5.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#ifndef client_h
#define client_h

#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <net/if.h>
#include <netdb.h>
#include <stdarg.h>
#include <string.h>
#include <sys/event.h>
#include <sys/errno.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>

#define MAXLINE 4096

#define MIN(a,b) a<b?a:b
#define MAX(a,b) a>b?a:b

typedef struct addrinfo Addrinfo;
typedef struct timespec Timespec;

int Tcp_connect(const char *host, const char *serv);

void err_dump(const char *, ...);
void err_msg(const char *, ...);
void err_quit(const char *, ...);
void err_ret(const char *, ...);
void err_sys(const char *, ...);

#endif /* client_h */
