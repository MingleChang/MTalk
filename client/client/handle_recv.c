//
//  handle_recv.c
//  client
//
//  Created by Mingle on 2018/3/14.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "client.h"

void handle_error_recv(Protocol head, void *data) {
    char *value = (char *)data;
    Data_error *error = dataErrorFromJsonString(value);
    err_msg("Error=>Code:%ld, Message:%s", error->code, error->msg);
    dataErrorFree(error);
}
void handle_test_recv(Protocol head, void *data) {
    char *value = (char *)data;
    err_msg("Test=>%s", value);
}
void handle_login_response_recv(Protocol head, void *data) {
    char *value = (char *)data;
    Login_response *response = loginResponseFromJsonString(value);
    size_t length = strlen(response->user_id) + 1;
    user_id = malloc(length);
    memset(user_id, 0, length);
    strcpy(user_id, response->user_id);
    user_id[length] = '\0';
    err_msg("Login Success:%s", user_id);
    loginResponseFree(response);
}
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
            handle_login_response_recv(head, data);
        }break;
        default:
            break;
    }
}

void Handle_recv(Protocol head, void *data) {
    handle_recv(head, data);
}
