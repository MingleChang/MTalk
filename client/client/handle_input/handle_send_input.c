//
//  handle_send_input.c
//  client
//
//  Created by Mingle on 2018/3/15.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "handle_send_input.h"
#include "client.h"

void handle_send_input(char *data) {
    if (user_id == NULL) {
        err_msg("你尚未登录， 请先登录");
        return;
    }
    char *value = data;
    char *sep = " ";
    char *to_user = strsep(&value, sep);
    char *message = strsep(&value, sep);
    if (to_user == NULL || message == NULL) {
        err_msg("send [user_id] [message]");
        return;
    }
    Send_msg_request *request = sendMsgRequestInit(0, user_id, to_user, message);
    char *json = sendMsgRequestToJsonString(request);
    Protocol head;
    head.version = PROTOCOL_VERSION;
    head.auth = PROTOCOL_AUTH;
    head.type = PROTOCOL_TYPE_SEND_MSG_REQ;
    head.length = (uint32_t)strlen(json) + 1;
    send_output(head, json);
    sendMsgRequestFree(request);
    free(json);
}
