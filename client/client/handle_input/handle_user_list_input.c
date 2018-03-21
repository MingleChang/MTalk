//
//  handle_user_list_input.c
//  client
//
//  Created by Mingle on 2018/3/15.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "handle_user_list_input.h"
#include "client.h"

void handle_user_list_input(char *data) {
    if (user_id == NULL) {
        err_msg("你尚未登录， 请先登录");
        return;
    }
    User_list_request *request = userListRequestInit(user_id);
    char *json = userListRequestToJsonString(request);
    struct protocol head;
    head.version = PROTOCOL_VERSION;
    head.auth = PROTOCOL_AUTH;
    head.type = PROTOCOL_TYPE_USER_LIST_REQ;
    head.length = (uint32_t)strlen(json) + 1;
    send_output(head, json);
    userListRequestFree(request);
    free(json);
}
