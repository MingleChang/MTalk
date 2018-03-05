//
//  client.c
//  test
//
//  Created by Mingle on 2018/3/5.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "client.h"
#include "protocol.h"

int main(int argc, const char * argv[]) {
    char *host = "127.0.0.1";
    char *serv = "8000";
    int sockfd, maxfdpi;
    size_t n;
    fd_set rset;
    struct protocol_head head;
    head.version = PROTOCOL_VERSION;
    head.auth = PROTOCOL_AUTH;
    head.no = 0;
    head.type = PROTOCOL_TYPE_TEST;
    head.length = 0;
    char sendline[MAXLINE], recvline[MAXLINE];
    
    sockfd = Tcp_connect(host, serv);
    FD_ZERO(&rset);
    for (;;) {
        FD_SET(fileno(stdin), &rset);
        FD_SET(sockfd, &rset);
        maxfdpi = MAX(fileno(stdin), sockfd) + 1;
        select(maxfdpi, &rset, NULL, NULL, NULL);
        if (FD_ISSET(sockfd, &rset)) {
            n = read(sockfd, sendline, MAXLINE);
            if (n <= 0) {
                exit(1);
            }
            fputs(sendline, stdout);
        }
        if (FD_ISSET(fileno(stdin), &rset)) {
            char buf[MAXLINE];
            if (fgets(buf, MAXLINE, stdin) == NULL) {
                continue;
            }
            n = strlen(buf);
            head.length = n;
            memcpy(sendline, &head, sizeof(struct protocol_head));
            memcpy(sendline + sizeof(struct protocol_head), buf, n);
            write(sockfd, sendline, sizeof(struct protocol_head) + n);
        }
    }
    
    return 0;
}
