//
//  send_message.h
//  server
//
//  Created by Mingle on 2018/3/22.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#ifndef send_message_h
#define send_message_h

#include <stdio.h>
#include "typedefs.h"

struct send_message {
    char *id;
    uint32_t type;
    char *from;
    char *to;
    char *value;
};
typedef struct send_message Send_message;

Send_message *sendMessageInit(char *id, uint32_t type, char *from, char *to, char *value);
Send_message *sendMessageFromJsonString(char *json);
char *sendMessageToJsonString(Send_message *message);
void sendMessageFree(Send_message *message);

#endif /* send_message_h */
