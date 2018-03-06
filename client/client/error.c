//
//  error.c
//  test
//
//  Created by Mingle on 2018/3/5.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "client.h"

static void    err_doit(int, const char *, va_list);

char    *pname = NULL;


void err_ret(const char *fmt, ...) {
    va_list        ap;
    
    va_start(ap, fmt);
    err_doit(1, fmt, ap);
    va_end(ap);
    return;
}

void err_sys(const char *fmt, ...) {
    va_list        ap;
    
    va_start(ap, fmt);
    err_doit(1, fmt, ap);
    va_end(ap);
    exit(1);
}

void err_dump(const char *fmt, ...) {
    va_list        ap;
    
    va_start(ap, fmt);
    err_doit(1, fmt, ap);
    va_end(ap);
    abort();
    //    exit(1);
}

void err_msg(const char *fmt, ...) {
    va_list        ap;
    
    va_start(ap, fmt);
    err_doit(0, fmt, ap);
    va_end(ap);
    return;
}

void err_quit(const char *fmt, ...) {
    va_list        ap;
    
    va_start(ap, fmt);
    err_doit(0, fmt, ap);
    va_end(ap);
    exit(1);
}

static void err_doit(int errnoflag, const char *fmt, va_list ap) {
    int        errno_save;
    char    buf[MAXLINE];
    
    errno_save = errno;        /* value caller might want printed */
    vsprintf(buf, fmt, ap);
    if (errnoflag)
        sprintf(buf+strlen(buf), ": %s", strerror(errno_save));
    strcat(buf, "\n");
    fflush(stdout);        /* in case stdout and stderr are the same */
    fputs(buf, stderr);
    fflush(stderr);        /* SunOS 4.1.* doesn't grok NULL argument */
    return;
}


