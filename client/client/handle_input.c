//
//  handle_input.c
//  client
//
//  Created by Mingle on 2018/3/13.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "handle_input.h"
#include "client.h"

void handle_test_input(char *data) {
    char *value = data;
    if (value == NULL) {
        err_msg("test [string]");
        return;
    }
    Protocol head;
    head.version = PROTOCOL_VERSION;
    head.auth = PROTOCOL_AUTH;
    head.type = PROTOCOL_TYPE_TEST;
    head.length = (uint32_t)strlen(value);
    send_output(head, value);
}

void handle_login_input(char *data) {
    if (user_id != NULL) {
        err_msg("您已登录：%s\n如需要登录清先退出",user_id);
        return;
    }
    char *value = data;
    char *sep = " ";
    char *username = strsep(&value, sep);
    char *password = strsep(&value, sep);
    if (username == NULL || password == NULL) {
        err_msg("login [username] [password]");
        return;
    }
    Login_request *request = loginRequestInit(username, password);
    char *json = loginRequestToJsonString(request);
    Protocol head;
    head.version = PROTOCOL_VERSION;
    head.auth = PROTOCOL_AUTH;
    head.type = PROTOCOL_TYPE_LOGIN_REQ;
    head.length = (uint32_t)strlen(json);
    send_output(head, json);
    loginRequestFree(request);
    free(json);
}

void handle_input(char *input) {
    char *value = input;
    char *sep = " ";
    char *command = strsep(&value, sep);
    if (strcmp(command, "test") == 0) {
        handle_test_input(value);
    }
    if (strcmp(command, "login") == 0) {
        handle_login_input(value);
    }
}

void Handle_input(char *input) {
    handle_input(input);
}
