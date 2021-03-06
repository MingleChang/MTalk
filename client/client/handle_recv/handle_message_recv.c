//
//  handle_message_recv.c
//  client
//
//  Created by Mingle on 2018/3/16.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "handle_message_recv.h"
#include "client.h"

void handle_message_recv(struct protocol head, void *data) {
    char *value = (char *)data;
    Recv_message *message = recvMessageFromJsonString(value);
    err_msg("recv message\n id:%s\n from:%s\n content:%s",message->id, message->from, message->value);
}
