//
//  base_socket.c
//  server
//
//  Created by Mingle on 2018/2/27.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "base_socket.h"

Base_socket *base_socket_init (int fd) {
    Base_socket *base = (Base_socket *)malloc(sizeof(Base_socket));
    base->fd = fd;
    base->next = NULL;
    return base;
}


void base_socket_add (Base_socket *base, int fd) {
    Base_socket *temp_socket = base;
    while (temp_socket->next != NULL) {
        temp_socket = temp_socket->next;
    }
    Base_socket *socket = Base_socket_init(fd);
    temp_socket->next = socket;
}

void base_socket_remove (Base_socket *base, int fd) {
    Base_socket *pre = base;
    Base_socket *temp_socket = base->next;
    while (temp_socket != NULL) {
        if (temp_socket->fd == fd) {
            pre->next = temp_socket->next;
            free(temp_socket);
            break;
        }else {
            pre = temp_socket;
            temp_socket = temp_socket->next;
        }
    }
}

void base_socket_free (Base_socket *base) {
    Base_socket *pre;
    Base_socket *temp_socket = base;
    while (temp_socket != NULL) {
        pre = temp_socket;
        temp_socket = temp_socket->next;
        free(pre);
    }
}

Base_socket *Base_socket_init(int fd) {
    return base_socket_init(fd);
}

void Base_socket_add (Base_socket *base, int fd) {
    base_socket_add(base, fd);
}
void Base_socket_remove (Base_socket *base, int fd) {
    base_socket_remove(base, fd);
}
void Base_socket_free (Base_socket *base) {
    base_socket_free(base);
}
