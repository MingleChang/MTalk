//
//  handle_user_list.c
//  server
//
//  Created by Mingle on 2018/3/15.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "handle_user_list.h"
#include "server.h"

int handleUserList(struct base_socket *socket) {
    char *value = socket->data_buff;
    User_list_request *request = userListRequestFromJsonString(value);
    if (strcmp(request->user_id, socket->user_id) != 0) {
        return -1;
    }
    cJSON *root = cJSON_CreateArray();
    struct base_socket *con_socket = base_socket_list->next;
    while (con_socket != NULL) {
        if (strlen(con_socket->user_id) > 0) {
            cJSON *item = cJSON_CreateString(con_socket->user_id);
            cJSON_AddItemToArray(root, item);
        }
        con_socket = con_socket->next;
    }
    char *json = cJSON_Print(root);
    struct protocol head;
    head.version = PROTOCOL_VERSION;
    head.auth = PROTOCOL_AUTH;
    head.type = PROTOCOL_TYPE_USER_LIST_RES;
    head.no = socket->head.no;
    head.length = (uint32_t)strlen(json) + 1;
    Send_data(socket->fd, head, json);
    cJSON_Delete(root);
    free(json);
    return 0;
}
