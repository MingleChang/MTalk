//
//  handle.c
//  server
//
//  Created by Mingle on 2018/3/15.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "server.h"
#include "handle_test.h"
#include "handle_heart_beat.h"
#include "handle_login.h"
#include "handle_user_list.h"
#include "handle_send.h"

int handle(struct base_socket *socket) {
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
        case PROTOCOL_TYPE_REGISTER_REQ:{
            
        }break;
        case PROTOCOL_TYPE_LOGOUT_REQ:{
            
        }break;
        case PROTOCOL_TYPE_USER_INFO_REQ:{
            
        }break;
        case PROTOCOL_TYPE_USER_LIST_REQ:{
            return handleUserList(socket);
        }break;
        case PROTOCOL_TYPE_SEND_MSG_REQ:{
            return handleSend(socket);
        }break;
        default:
            break;
    }
    return 0;
}

int Handle(struct base_socket *socket) {
    return handle(socket);
}
