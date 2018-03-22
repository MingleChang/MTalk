//
//  recv_message.h
//  server
//
//  Created by Mingle on 2018/3/22.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#ifndef recv_message_h
#define recv_message_h

#include <stdio.h>
#include "typedefs.h"

struct recv_message {
    char *id;
    uint32_t type;
    char *from;
    char *to;
    char *value;
};
typedef struct recv_message Recv_message;

Recv_message *recvMessageInit(char *id, uint32_t type, char *from, char *to, char *value);
Recv_message *recvMessageFromJsonString(char *json);
char *recvMessageToJsonString(Recv_message *message);
void recvMessageFree(Recv_message *message);

#endif /* recv_message_h */
