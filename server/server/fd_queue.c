//
//  fd_queue.c
//  server
//
//  Created by Mingle on 2018/2/27.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "server.h"

int fd_queue_init() {
    int result = kqueue();
    return result;
}

void fd_queue_add_event(int fq, int fd, uint8_t event) {
    struct kevent ke;
    if ((event & SOCKET_READ) != 0) {
        EV_SET(&ke, fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
        kevent(fq, &ke, 1, NULL, 0, NULL);
    }
    if ((event & SOCKET_WRITE) != 0) {
        EV_SET(&ke, fd, EVFILT_WRITE, EV_ADD, 0, 0, NULL);
        kevent(fq, &ke, 1, NULL, 0, NULL);
    }
}

void fd_queue_delete_event(int fq, int fd, uint8_t event) {
    struct kevent ke;
    if ((event & SOCKET_READ) != 0) {
        EV_SET(&ke, fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
        kevent(fq, &ke, 1, NULL, 0, NULL);
    }
    if ((event & SOCKET_WRITE) != 0) {
        EV_SET(&ke, fd, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
        kevent(fq, &ke, 1, NULL, 0, NULL);
    }
}


int Fd_queue_init(void) {
    return fd_queue_init();
}
void Fd_queue_add_event(int fq, int fd, uint8_t event) {
    fd_queue_add_event(fq, fd, event);
}
void Fd_queue_delete_event(int fq, int fd, uint8_t event) {
    fd_queue_delete_event(fq, fd, event);
}
