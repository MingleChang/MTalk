//
//  send_msg_request.h
//  server
//
//  Created by Mingle on 2018/3/15.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#ifndef send_msg_request_h
#define send_msg_request_h

#include <stdio.h>
#include "typedefs.h"

struct send_msg_request {
    uint32_t type;
    char *from_user;
    char *to_user;
    char *message;
};
typedef struct send_msg_request Send_msg_request;

Send_msg_request *sendMsgRequestInit(uint32_t type, char *from_user, char *to_user, char *message);
Send_msg_request *sendMsgRequestFromJsonString(char *json);
char *sendMsgRequestToJsonString(Send_msg_request *request);
void sendMsgRequestFree(Send_msg_request *request);

#endif /* send_msg_request_h */
