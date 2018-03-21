//
//  send_output.c
//  client
//
//  Created by Mingle on 2018/3/13.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "client.h"

void send_output(struct protocol head, char *data) {
    head.no = req_no++;
    char *buff = (char *)malloc(sizeof(head) + head.length);
    memcpy(buff, &head, sizeof(struct protocol));
    memcpy(buff + sizeof(struct protocol), data, head.length);
    write(sockfd, buff, sizeof(struct protocol) + head.length);
    free(buff);
}

void Send_output(struct protocol head, char *data) {
    send_output(head, data);
}
