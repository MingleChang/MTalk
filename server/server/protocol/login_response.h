//
//  login_response.h
//  server
//
//  Created by Mingle on 2018/3/15.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#ifndef login_response_h
#define login_response_h

#include <stdio.h>

struct login_response {
    char *user_id;//创建一个用户id返回
};
typedef struct login_response Login_response;
Login_response *loginResponseFromJsonString(char *json);
char *loginResponseToJsonString(Login_response *response);
void loginResponseFree(Login_response *response);

#endif /* login_response_h */
