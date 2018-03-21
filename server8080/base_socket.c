//
//  base_socket.c
//  server
//
//  Created by Mingle on 2018/2/27.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "base_socket.h"
#include "server.h"

struct base_socket *base_socket_init (int fd) {
    struct base_socket *base = (struct base_socket *)malloc(sizeof(struct base_socket));
    base->fd = fd;
    base->heartbeat = HEART_BEAT;
    base->head_buff = NULL;
    base->head_buff_len = 0;
    base->data_buff = NULL;
    base->data_buff_len = 0;
    memset(&base->user_id, 0, 33);
    base->next = NULL;
    return base;
}


void base_socket_add (struct base_socket *base, int fd) {
    struct base_socket *temp_socket = base;
    while (temp_socket->next != NULL) {
        temp_socket = temp_socket->next;
    }
    struct base_socket *socket = Base_socket_init(fd);
    temp_socket->next = socket;
}

void base_socket_remove (struct base_socket *base, int fd) {
    struct base_socket *pre = base;
    struct base_socket *temp_socket = base->next;
    while (temp_socket != NULL) {
        if (temp_socket->fd == fd) {
            pre->next = temp_socket->next;
            Base_socket_free(temp_socket);
            break;
        }else {
            pre = temp_socket;
            temp_socket = temp_socket->next;
        }
    }
}

void base_socket_clear(struct base_socket *base) {
    base->head_buff_len = 0;
    if (base->head_buff != NULL) {
        free(base->head_buff);
        base->head_buff = NULL;
    }
    base->data_buff_len = 0;
    if (base->data_buff != NULL) {
        free(base->data_buff);
        base->data_buff = NULL;
    }
}

void base_socket_free (struct base_socket *base) {
    Base_socket_clear(base);
    free(base);
}

void base_socket_free_all (struct base_socket *base) {
    struct base_socket *pre;
    struct base_socket *temp_socket = base;
    while (temp_socket != NULL) {
        pre = temp_socket;
        temp_socket = temp_socket->next;
        Base_socket_free(temp_socket);
    }
}

struct base_socket *base_socket_find(struct base_socket *base, int fd) {
    struct base_socket *temp_socket = base;
    while (temp_socket != NULL) {
        if (temp_socket->fd == fd) {
            return temp_socket;
        }else {
            temp_socket = temp_socket->next;
        }
    }
    return temp_socket;
}

void base_socket_read(struct base_socket *base) {
    ssize_t n;
    size_t max_length;
    char buff[MAXLINE];
    memset(buff, 0, MAXLINE);
    int connfd = base->fd;
    if (base->head_buff_len < sizeof(struct protocol)) {
        max_length = sizeof(struct protocol) - base->head_buff_len;
        n = read(connfd, buff, max_length);
        if (n > 0) {
            base->head_buff = realloc(base->head_buff, base->head_buff_len + n);
            memcpy(base->head_buff + base->head_buff_len, buff, n);
            base->head_buff_len = base->head_buff_len + n;
            if (base->head_buff_len == sizeof(struct protocol)) {
                memcpy(&base->head, base->head_buff, base->head_buff_len);
            }
        }
    }else {
        max_length = MIN(base->head.length - base->data_buff_len, MAXLINE);
        n = read(connfd, buff, max_length);
        if (n > 0) {
            base->data_buff = realloc(base->data_buff, base->data_buff_len + n);
            memcpy(base->data_buff + base->data_buff_len, buff, n);
            base->data_buff_len = base->data_buff_len + n;
        }
    }
    if (n <= 0) {
        Base_socket_remove(base_socket_list, connfd);
        Fd_queue_delete_event(global_fq, connfd, SOCKET_READ | SOCKET_EXCEP);
        close(connfd);
    }
    if (base->head_buff_len == sizeof(struct protocol) && base->data_buff_len == base->head.length) {
        //处理数据
        Handle(base);
        //清除缓存
        Base_socket_clear(base);
    }
}

void base_socket_heart_beat (void) {
    struct base_socket *pre = base_socket_list;
    struct base_socket *temp_socket = pre->next;
    while (temp_socket != NULL) {
        temp_socket->heartbeat--;
        err_msg("fd:%ld  heartbeat:%ld", temp_socket->fd, temp_socket->heartbeat);
        if (temp_socket->heartbeat <= 0) {
            Base_socket_close(temp_socket);
            temp_socket = pre->next;
        }else {
            pre = temp_socket;
            temp_socket = temp_socket->next;
        }
    }
}
void base_socket_close(struct base_socket *base) {
    close(base->fd);
    Base_socket_remove(base_socket_list, base->fd);
}
struct base_socket *Base_socket_init(int fd) {
    return base_socket_init(fd);
}

void Base_socket_add (struct base_socket *base, int fd) {
    base_socket_add(base, fd);
}
void Base_socket_remove (struct base_socket *base, int fd) {
    base_socket_remove(base, fd);
}
void Base_socket_clear(struct base_socket *base) {
    base_socket_clear(base);
}
void Base_socket_free (struct base_socket *base) {
    base_socket_free(base);
}
void Base_socket_free_all (struct base_socket *base) {
    base_socket_free_all(base);
}
struct base_socket *Base_socket_find(struct base_socket *base, int fd) {
    return base_socket_find(base, fd);
}

void Base_socket_read(struct base_socket *base) {
    base_socket_read(base);
}
void Base_socket_heart_beat (void) {
    base_socket_heart_beat();
}
void Base_socket_close(struct base_socket *base) {
    base_socket_close(base);
}
