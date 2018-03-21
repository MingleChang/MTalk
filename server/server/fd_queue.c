//
//  fd_queue.c
//  server
//
//  Created by Mingle on 2018/2/27.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "server.h"

#ifdef __APPLE__

#include <sys/event.h>
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
void fd_queue_dispatch(int fq, void (*callback)(int fd, uint8_t event)) {
    struct kevent eventList[MAXLINE];
    int n = kevent(fq, NULL, 0, eventList, MAXLINE, NULL);
    int i = 0;
    for (i = 0; i < n; i++) {
        struct kevent event = eventList[i];
        if (event.filter == EVFILT_READ) {
            callback((int)event.ident, SOCKET_READ);
        }else if (event.filter == EVFILT_WRITE) {
            callback((int)event.ident, SOCKET_WRITE);
        }
    }
}
#else

#include <sys/epoll.h>
int fd_queue_init() {
    int result = epoll_create(MAXLINE);
    return result;
}
void fd_queue_add_event(int fq, int fd, uint8_t event) {
    struct epoll_event ev;
    //边缘触发
    ev.events = EPOLLIN | EPOLLOUT | EPOLLPRI | EPOLLERR | EPOLLHUP;
    //水平触发
//    ev.events = EPOLLIN | EPOLLOUT | EPOLLET | EPOLLPRI | EPOLLERR | EPOLLHUP;
    ev.data.fd = fd;
    epoll_ctl(fq, EPOLL_CTL_ADD, fd, &ev);
}
void fd_queue_delete_event(int fq, int fd, uint8_t event) {
    epoll_ctl(fq, EPOLL_CTL_DEL, fd, NULL)
}
void fd_queue_dispatch(int fq, void (*callback)(int fd, uint8_t event)) {
    struct epoll_event events[MAXLINE];
    int nfds = epoll_wait(fq, events, MAXLINE, NULL);
    int i = 0;
    for (i = 0; i < nfds; i++) {
        int fd = events[i].data.fd;
        if (events[i].events & EPOLLIN) {
            callback(fd, SOCKET_READ);
        }
        if (events[i].events & EPOLLOUT) {
            callback(fd, SOCKET_WRITE);
        }
        if (events[i].events & (EPOLLPRI | EPOLLERR | EPOLLHUP)) {
            callback(fd, SOCKET_EXCEP);
        }
    }
}
#endif

int Fd_queue_init(void) {
    return fd_queue_init();
}
void Fd_queue_add_event(int fq, int fd, uint8_t event) {
    fd_queue_add_event(fq, fd, event);
}
void Fd_queue_delete_event(int fq, int fd, uint8_t event) {
    fd_queue_delete_event(fq, fd, event);
}
void Fd_queue_dispatch(int fq, void (*callback)(int fd, uint8_t event)) {
    fd_queue_dispatch(fq, callback);
}
