//
//  handle_login.c
//  server
//
//  Created by Mingle on 2018/3/15.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "handle_login.h"
#include "server.h"

int handleLogin(Base_socket *socket) {
    char *value = socket->data_buff;
    Login_request *request = loginRequestFromJsonString(value);
    err_msg("login=>username:%s, password:%s",request->username, request->password);
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
    head.length = (uint32_t)strlen(json) + 1;
    Send_data(socket->fd, head, json);
    free(json);
    return 0;
}
