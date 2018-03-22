//
//  handle_logout_input.c
//  client
//
//  Created by Mingle on 2018/3/22.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "handle_logout_input.h"
#include "client.h"

void handle_logout_input(char *data) {
    if (user_id == NULL) {
        err_msg("你尚未登录， 请先登录");
        return;
    }
    Logout_request *request = logoutRequestInit(user_id);
    char *json = logoutRequestToJsonString(request);
    struct protocol head;
    head.version = PROTOCOL_VERSION;
    head.auth = PROTOCOL_AUTH;
    head.type = PROTOCOL_TYPE_LOGOUT_REQ;
    head.length = (uint32_t)strlen(json) + 1;
    send_output(head, json);
    logoutRequestFree(request);
    free(json);
}
