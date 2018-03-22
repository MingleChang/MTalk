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
char *user_id;

static void sig_alrm(int signo) {
    struct protocol head;
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
    user_id = NULL;
//    char *host = "45.77.197.226";
    char *host = "127.0.0.1";
    char *serv = "8080";
    int maxfdpi;
    ssize_t n;
    size_t max_length = 0;
    fd_set rset;
    struct protocol head;
    void *head_buff = NULL, *data_buff = NULL;
    ssize_t head_buff_len = 0, data_buff_len = 0;
    char buff[MAXLINE];
    
    sockfd = Tcp_connect(host, serv);
    Set_non_block(sockfd);
    Set_non_block(STDIN_FILENO);
    err_msg("Connect Success...");
    err_msg("test [string]");
    err_msg("login [username] [password]");
    err_msg("logout");
    err_msg("userlist");
    err_msg("send [user_id] [message]");
    FD_ZERO(&rset);
    signal(SIGALRM, sig_alrm);
    alarm(HEART_BEAT);
    for (;;) {
        memset(&buff, 0, MAXLINE);
        FD_SET(STDIN_FILENO, &rset);
        FD_SET(sockfd, &rset);
        maxfdpi = MAX(fileno(stdin), sockfd) + 1;
        select(maxfdpi, &rset, NULL, NULL, NULL);
        if (FD_ISSET(sockfd, &rset)) {
            if (head_buff_len < sizeof(struct protocol)) {
                max_length = sizeof(struct protocol) -  head_buff_len;
                n = read(sockfd, buff, max_length);
                if (n > 0) {
                    head_buff = realloc(head_buff, head_buff_len + n);
                    memcpy(head_buff + head_buff_len, buff, n);
                    head_buff_len = head_buff_len + n;
                    if (head_buff_len == sizeof(struct protocol)) {
                        memcpy(&head, head_buff, head_buff_len);
                    }
                }
            }else {
                max_length = MIN(head.length - data_buff_len, MAXLINE);
                n = read(sockfd, buff, max_length);
                if (n > 0) {
                    data_buff = realloc(data_buff, data_buff_len + n);
                    memcpy(data_buff + data_buff_len, buff, n);
                    data_buff_len = data_buff_len + n;
                }
            }
            if (n <= 0) {
                if (errno != EAGAIN && errno != EWOULDBLOCK) {
                    err_msg("Error:%d %d",errno, n);
                    close(sockfd);
                    break;
                }
            }
            if (head_buff_len == sizeof(struct protocol) && data_buff_len == head.length) {
                Handle_recv(head, data_buff);
                if (head_buff != NULL) {
                    free(head_buff);
                    head_buff = NULL;
                }
                head_buff_len = 0;
                if (data_buff != NULL) {
                    free(data_buff);
                    data_buff = NULL;
                }
                data_buff_len = 0;
            }
        }
        if (FD_ISSET(STDIN_FILENO, &rset)) {
            n = read(STDIN_FILENO, buff, MAXLINE);
            if (n<=0) {
                continue;
            }
            buff[n] = '\0';
            Handle_input(buff);
        }
    }
    
    return 0;
}
