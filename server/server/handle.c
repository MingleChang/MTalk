//
//  handle.c
//  server
//
//  Created by Mingle on 2018/3/8.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "server.h"

//处理PROTOCOL_TYPE_TEST类型数据
int handleTest(Base_socket *socket) {
    Base_socket *con_socket = base_socket_list->next;
    while (con_socket != NULL) {
        write(con_socket->fd, socket->data_buff, socket->data_buff_len);
        con_socket = con_socket->next;
    }
    return 0;
}
//处理PROTOCOL_TYPE_HEART_BEAT类型数据
int handleHeartBeat(Base_socket *socket) {
    socket->heartbeat = HEART_BEAT;
    return 0;
}

int handle(Base_socket *socket) {
    if (socket->head.auth != PROTOCOL_AUTH) {
        err_msg("Auth is Error");
        Base_socket_close(socket);
        return -1;
    }
    switch (socket->head.type) {
        case PROTOCOL_TYPE_TEST:{
            return handleTest(socket);
        }break;
        case PROTOCOL_TYPE_HEART_BEAT:{
            return handleHeartBeat(socket);
        }break;
            
        default:
            break;
    }
    return 0;
}

int Handle(Base_socket *socket) {
    return handle(socket);
}
