//
//  logout_request.h
//  server
//
//  Created by Mingle on 2018/3/15.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#ifndef logout_request_h
#define logout_request_h

#include <stdio.h>

struct logout_request {
    char *user_id;
};
typedef struct logout_request Logout_request;

Logout_request *logoutRequestInit(char *user_id);
Logout_request *logoutRequestFromJsonString(char *json);
char *logoutRequestToJsonString(Logout_request *request);
void logoutRequestFree(Logout_request *request);

#endif /* logout_request_h */
