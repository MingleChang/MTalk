//
//  user_list_request.h
//  server
//
//  Created by Mingle on 2018/3/15.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#ifndef user_list_request_h
#define user_list_request_h

#include <stdio.h>

struct user_list_request {
    char *user_id;
};
typedef struct user_list_request User_list_request;

User_list_request *userListRequestInitWithUserId(char *user_id);
User_list_request *userListRequestFromJsonString(char *json);
char *userListRequestToJsonString(User_list_request *request);
void userListRequestFree(User_list_request *request);

#endif /* user_list_request_h */
