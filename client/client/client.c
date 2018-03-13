//
//  client.c
//  test
//
//  Created by Mingle on 2018/3/5.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "client.h"

int sockfd;
uint32_t req_no;

static void sig_alrm(int signo) {
    Protocol head;
    head.version = PROTOCOL_VERSION;
    head.auth = PROTOCOL_AUTH;
    head.no = 0;
    head.type = PROTOCOL_TYPE_HEART_BEAT;
    head.length = 0;
    send_output(head, NULL);
    alarm(HEART_BEAT);
}

int main(int argc, const char * argv[]) {
    req_no = 0;
    char *host = "127.0.0.1";
    char *serv = "8000";
    int maxfdpi;
    size_t n;
    fd_set rset;
    void *head_buff, *data_buff;
    ssize_t head_buff_len, data_buff_len;
    char buff[MAXLINE];
    
    Protocol head;
    head.version = PROTOCOL_VERSION;
    head.auth = PROTOCOL_AUTH;
    head.no = 0;
    head.type = PROTOCOL_TYPE_TEST;
    head.length = 0;
    char recvline[MAXLINE];
    
    sockfd = Tcp_connect(host, serv);
    err_msg("Connect Success...");
    err_msg("login [username] [password]");
    FD_ZERO(&rset);
    signal(SIGALRM, sig_alrm);
    alarm(HEART_BEAT);
    for (;;) {
        FD_SET(fileno(stdin), &rset);
        FD_SET(sockfd, &rset);
        maxfdpi = MAX(fileno(stdin), sockfd) + 1;
        select(maxfdpi, &rset, NULL, NULL, NULL);
        if (FD_ISSET(sockfd, &rset)) {
            n = read(sockfd, recvline, MAXLINE);
            if (n <= 0) {
                return -1;
            }
            fputs(recvline, stdout);
        }
        if (FD_ISSET(fileno(stdin), &rset)) {
            memset(&buff, 0, MAXLINE);
            
            if (fgets(buff, MAXLINE, stdin) == NULL) {
                continue;
            }
            buff[strlen(buff) - 1] = '\0';
            Handle_input(buff);
//            n = strlen(buff);
//            char *p = strtok(buff, " ");
//            head.length = n;
//            memcpy(recvline, &head, sizeof(Protocol));
//            memcpy(recvline + sizeof(Protocol), buff, n);
//            write(sockfd, recvline, sizeof(Protocol) + n);
        }
    }
    
    return 0;
}
