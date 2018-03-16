//
//  handle_send.c
//  server
//
//  Created by Mingle on 2018/3/15.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "handle_send.h"
#include "server.h"

int handleSend(Base_socket *socket) {
    Protocol head;
    head.version = PROTOCOL_VERSION;
    head.auth = PROTOCOL_AUTH;
    head.type = PROTOCOL_TYPE_SEND_MSG_RES;
    head.no = socket->head.no;
    head.length = 0;
    Send_data(socket->fd, head, NULL);
    char *value = (char *)socket->data_buff;
    Send_msg_request *request = sendMsgRequestFromJsonString(value);
    Base_socket *temp_socket = base_socket_list->next;
    while (temp_socket != NULL) {
        if (strcmp(temp_socket->user_id, request->to_user) == 0) {
            char *uuid = Create_uuid();
            Message *message = messageInit(uuid, request->type, request->from_user, request->to_user, request->message);
            char *json = messageToJsonString(message);
            Protocol messageHead;
            messageHead.version = PROTOCOL_VERSION;
            messageHead.auth = PROTOCOL_AUTH;
            messageHead.type = PROTOCOL_TYPE_SEND_MSG;
            messageHead.length = (uint32_t)strlen(json) + 1;
            Send_data(temp_socket->fd, messageHead, json);
            messageFree(message);
            free(uuid);
            free(json);
            break;
        }
        temp_socket = temp_socket->next;
    }
    return 0;
}
