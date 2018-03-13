//
//  send_output.c
//  client
//
//  Created by Mingle on 2018/3/13.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "client.h"

void send_output(Protocol head, char *data) {
    head.no = req_no++;
    char *buff = (char *)malloc(sizeof(head) + head.length);
    memcpy(buff, &head, sizeof(Protocol));
    memcpy(buff + sizeof(Protocol), data, head.length);
    write(sockfd, buff, sizeof(Protocol) + head.length);
}

void Send_output(Protocol head, char *data) {
    send_output(head, data);
}
