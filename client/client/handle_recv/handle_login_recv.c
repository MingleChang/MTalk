//
//  handle_login_recv.c
//  client
//
//  Created by Mingle on 2018/3/15.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "handle_login_recv.h"
#include "client.h"

void handle_login_recv(struct protocol head, void *data) {
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
