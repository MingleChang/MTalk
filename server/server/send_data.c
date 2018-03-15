//
//  send_data.c
//  server
//
//  Created by Mingle on 2018/3/14.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "server.h"

void send_data(int fd, Protocol head, char *data) {
    char *buff = (char *)malloc(sizeof(head) + head.length);
    memcpy(buff, &head, sizeof(Protocol));
    memcpy(buff + sizeof(Protocol), data, head.length);
    write(fd, buff, sizeof(Protocol) + head.length);
    err_msg("send to %d type %d data %s", fd, head.type, data);
    free(buff);
}

void Send_data(int fd, Protocol head, char *data) {
    send_data(fd, head, data);
}
