//
//  handle_recv.c
//  client
//
//  Created by Mingle on 2018/3/15.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "handle_recv.h"
#include "client.h"
#include "handle_test_recv.h"
#include "handle_error_recv.h"
#include "handle_login_recv.h"
#include "handle_user_list_recv.h"
#include "handle_send_recv.h"
#include "handle_message_recv.h"

void handle_recv(Protocol head, void *data) {
    if (head.auth != PROTOCOL_AUTH) {
        err_msg("Auth is Error");
        return;
    }
    switch (head.type) {
        case PROTOCOL_TYPE_ERROR:{
            handle_error_recv(head, data);
        }break;
        case PROTOCOL_TYPE_TEST:{
            handle_test_recv(head, data);
        }break;
        case PROTOCOL_TYPE_LOGIN_RES:{
            handle_login_recv(head, data);
        }break;
        case PROTOCOL_TYPE_REGISTER_RES:{
            
        }break;
        case PROTOCOL_TYPE_LOGOUT_RES:{
            
        }break;
        case PROTOCOL_TYPE_USER_INFO_RES:{
            
        }break;
        case PROTOCOL_TYPE_USER_LIST_RES:{
            handle_user_list_recv(head, data);
        }break;
        case PROTOCOL_TYPE_SEND_MSG_RES:{
            handle_send_recv(head, data);
        }break;
        case PROTOCOL_TYPE_RECV_MSG:{
            handle_message_recv(head, data);
        }break;
        default:
            break;
    }
}

void Handle_recv(Protocol head, void *data) {
    handle_recv(head, data);
}
