//
//  message.h
//  server
//
//  Created by Mingle on 2018/3/22.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#ifndef message_h
#define message_h

#include <stdio.h>
#include "typedefs.h"

struct message {
    char *id;
    uint32_t type;
    char *from;
    char *to;
    char *value;
};
typedef struct message Message;

Message *messageInit(char *id, uint32_t type, char *from, char *to, char *value);
Message *messageFromJsonString(char *json);
char *messageToJsonString(Message *message);
void messageFree(Message *message);

#endif /* message_h */
