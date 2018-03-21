//
//  login_request.h
//  server
//
//  Created by Mingle on 2018/3/15.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#ifndef login_request_h
#define login_request_h

#include <stdio.h>

struct login_request {
    char *username;
    char *password;
};
typedef struct login_request Login_request;

Login_request *loginRequestInit(char *username, char *password);
Login_request *loginRequestFromJsonString(char *json);
char *loginRequestToJsonString(Login_request *request);
void loginRequestFree(Login_request *request);

#endif /* login_request_h */
