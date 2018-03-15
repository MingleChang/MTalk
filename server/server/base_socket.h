//
//  base_socket.h
//  server
//
//  Created by Mingle on 2018/2/27.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#ifndef base_socket_h
#define base_socket_h

#include <stdlib.h>
#include <stdio.h>
#include "protocol.h"

struct base_socket {
    int fd;
    int heartbeat; //心跳
    
    void *data_buff;
    ssize_t data_buff_len;
    
    void *head_buff;
    ssize_t head_buff_len;
    Protocol head;
    
    char user_id[33];
    
    struct base_socket *next;
};
typedef struct base_socket Base_socket;

Base_socket *Base_socket_init(int fd);
void Base_socket_add (Base_socket *base, int fd);
void Base_socket_remove (Base_socket *base, int fd);
void Base_socket_clear(Base_socket *base);
void Base_socket_free (Base_socket *base);
void Base_socket_free_all (Base_socket *base);

Base_socket *Base_socket_find(Base_socket *base, int fd);
void Base_socket_read(Base_socket *base);
void Base_socket_heart_beat (void);
void Base_socket_close(Base_socket *base);

#endif /* base_socket_h */
