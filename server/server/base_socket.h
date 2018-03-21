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
    struct protocol head;
    
    char user_id[33];
    
    struct base_socket *next;
};

struct base_socket *Base_socket_init(int fd);
void Base_socket_add (struct base_socket *base, int fd);
void Base_socket_remove (struct base_socket *base, int fd);
void Base_socket_clear(struct base_socket *base);
void Base_socket_free (struct base_socket *base);
void Base_socket_free_all (struct base_socket *base);

struct base_socket *Base_socket_find(struct base_socket *base, int fd);
void Base_socket_read(struct base_socket *base);
void Base_socket_heart_beat (void);
void Base_socket_close(struct base_socket *base);

#endif /* base_socket_h */
