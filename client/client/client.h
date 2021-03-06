//
//  client.h
//  test
//
//  Created by Mingle on 2018/3/5.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#ifndef client_h
#define client_h

#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <net/if.h>
#include <netdb.h>
#include <stdarg.h>
#include <string.h>
#include <sys/event.h>
#include <sys/errno.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <uuid/uuid.h>
#include <signal.h>
#include <netinet/tcp.h>
#include "utils.h"
#include "protocol.h"
#include "handle_input/handle_input.h"
#include "send_output.h"
#include "handle_recv.h"
#include "cJSON.h"

#define CLIENT

#define MAXLINE 4096
#define HEART_BEAT 30

#define MIN(a,b) a<b?a:b
#define MAX(a,b) a>b?a:b

extern int sockfd;
extern uint32_t req_no;
extern char *user_id;

typedef struct addrinfo Addrinfo;
typedef struct timespec Timespec;

int Tcp_connect(const char *host, const char *serv);

void err_dump(const char *, ...);
void err_msg(const char *, ...);
void err_quit(const char *, ...);
void err_ret(const char *, ...);
void err_sys(const char *, ...);

#endif /* client_h */
