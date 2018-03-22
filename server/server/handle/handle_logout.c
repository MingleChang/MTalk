//
//  handle_logout.c
//  server
//
//  Created by Mingle on 2018/3/22.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "handle_logout.h"
#include "server.h"

int handleLogout(struct base_socket *socket) {
    char *value = (char *)socket->data_buff;
    Logout_request *request = logoutRequestFromJsonString(value);
    if (strcmp(request->user_id, socket->user_id) != 0) {
        return -1;
    }
    memset(socket->user_id, 0, 33);
    struct protocol head;
    head.version = PROTOCOL_VERSION;
    head.auth = PROTOCOL_AUTH;
    head.type = PROTOCOL_TYPE_LOGOUT_RES;
    head.no = socket->head.no;
    head.length = 0;
    Send_data(socket->fd, &head, NULL);
    return 0;
}
