//
//  utils.c
//  server
//
//  Created by Mingle on 2018/3/9.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "server.h"
#include <uuid/uuid.h>

char *create_uuid(void) {
    char *result = (char *)malloc(33);
    memchr(result, 0, 33);
    uuid_t uuid;
    uuid_generate(uuid);
    int i = 0;
    for(i = 0; i < 16; i++) {
        char c[4];
        snprintf(c, 3, "%02X",uuid[i]);
        strcat(result, c);
    }
    return result;
}
void set_non_block(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}
void set_no_delay(int fd) {
    int enable = 1;
    setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (void*)&enable, sizeof(enable));
}
char *Create_uuid(void) {
    return create_uuid();
}

void Set_non_block(int fd) {
    set_non_block(fd);
}

void Set_no_delay(int fd) {
    set_no_delay(fd);
}
