//
//  utils.c
//  server
//
//  Created by Mingle on 2018/3/9.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "server.h"

char *create_uuid(void) {
    char *result = (char *)malloc(33);
    memchr(result, 0, 33);
    uuid_t uuid;
    uuid_generate(uuid);
    for(int i=0;i<16;i++) {
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

char *Create_uuid(void) {
    return create_uuid();
}

void Set_non_block(int fd) {
    set_non_block(fd);
}
