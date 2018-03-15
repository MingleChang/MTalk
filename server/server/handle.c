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
        Send_data(con_socket->fd, socket->head, socket->data_buff);
        con_socket = con_socket->next;
    }
    return 0;
}
//处理PROTOCOL_TYPE_HEART_BEAT类型数据
int handleHeartBeat(Base_socket *socket) {
    socket->heartbeat = HEART_BEAT;
    return 0;
}
//处理PROTOCOL_TYPE_LOGIN_REQ类型数据
int handleLogin(Base_socket *socket) {
    char *value = socket->data_buff;
    Login_request *request = loginRequestFromJsonString(value);
    err_msg("username:%s, password:%s",request->username, request->password);
    loginRequestFree(request);
    char *user_id = Create_uuid();
    memcpy(&socket->user_id, user_id, strlen(user_id));
    Login_response response;
    response.user_id = user_id;
    char *json = loginResponseToJsonString(&response);
    Protocol head;
    head.version = PROTOCOL_VERSION;
    head.auth = PROTOCOL_AUTH;
    head.type = PROTOCOL_TYPE_LOGIN_RES;
    head.no = socket->head.no;
    head.length = (uint32_t)strlen(json);
    Send_data(socket->fd, head, json);
    free(json);
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
        case PROTOCOL_TYPE_LOGIN_REQ:{
            return handleLogin(socket);
        }break;
        default:
            break;
    }
    return 0;
}

int Handle(Base_socket *socket) {
    return handle(socket);
}
