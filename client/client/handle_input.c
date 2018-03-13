//
//  handle_input.c
//  client
//
//  Created by Mingle on 2018/3/13.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "handle_input.h"
#include "client.h"

void handle_login(char *data) {
    char *value = data;
    char *sep = " ";
    char *username = strsep(&value, sep);
    char *password = strsep(&value, sep);
    if (username == NULL || password == NULL) {
        err_msg("login [username] [password]");
        return;
    }
    Login_request request;
    request.username = username;
    request.password = password;
    char *json = loginRequestToJsonString(&request);
    Protocol head;
    head.version = PROTOCOL_VERSION;
    head.auth = PROTOCOL_AUTH;
    head.type = PROTOCOL_TYPE_LOGIN_REQ;
    head.length = (uint32_t)strlen(json);
    send_output(head, json);
    free(json);
}

void handle_input(char *input) {
    char *value = input;
    char *sep = " ";
    char *command = strsep(&value, sep);
    if (strcmp(command, "login") == 0) {
        err_msg("登录\n");
        handle_login(value);
    }
}

void Handle_input(char *input) {
    handle_input(input);
}
