//
//  base_socket.h
//  server
//
//  Created by Mingle on 2018/2/27.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#ifndef base_socket_h
#define base_socket_h

#include "server.h"

struct base_socket {
    int fd;
    struct base_socket *next;
};
typedef struct base_socket Base_socket;

#endif /* base_socket_h */
