//
//  send_data.c
//  server
//
//  Created by Mingle on 2018/3/14.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "server.h"

void send_data(int fd, struct protocol *head, char *data) {
    char *buff = (char *)malloc(sizeof(struct protocol) + head->length);
    memcpy(buff, &head, sizeof(struct protocol));
    memcpy(buff + sizeof(struct protocol), data, head->length);
    write(fd, buff, sizeof(struct protocol) + head->length);
    err_msg("send to %d type %d data %s", fd, head->type, data);
    free(buff);
}

void Send_data(int fd, struct protocol *head, char *data) {
    send_data(fd, head, data);
}
