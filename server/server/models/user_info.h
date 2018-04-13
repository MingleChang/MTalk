//
//  user_info.h
//  server
//
//  Created by Mingle on 2018/3/22.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#ifndef user_info_h
#define user_info_h

#include <stdio.h>

struct user_info {
    char *id;
    char *username;
    char *password;
};
typedef struct user_info UserInfo;

UserInfo *userInfoInit(char *id, char *username, char *password);
UserInfo *userInfoFromJsonString(char *json);
char *userInfoToJsonString(UserInfo *user);
void userInfoFree(UserInfo *user);

void userInfoSetId(UserInfo *user, char *id);
void userInfoSetUsername(UserInfo *user, char *username);
void userInfoSetPassword(UserInfo *user, char *password);

#endif /* user_info_h */
