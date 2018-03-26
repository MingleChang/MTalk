//
//  user_info.c
//  server
//
//  Created by Mingle on 2018/3/22.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "user_info.h"
#include "cJSON.h"
#include <stdlib.h>
#include <string.h>

UserInfo *userInfoInit(char *id, char *username, char *password) {
    UserInfo *user = malloc(sizeof(UserInfo));
    size_t length;
    
    length = strlen(id) + 1;
    user->id = malloc(length);
    memset(user->id, 0, length);
    strcpy(user->id, id);
    user->id[length] = '\0';
    
    length = strlen(username) + 1;
    user->username = malloc(length);
    memset(user->username, 0, length);
    strcpy(user->username, username);
    user->username[length] = '\0';
    
    length = strlen(password) + 1;
    user->password = malloc(length);
    memset(user->password, 0, length);
    strcpy(user->password, password);
    user->password[length] = '\0';
    return user;
}
UserInfo *userInfoFromJsonString(char *json) {
    cJSON *root = cJSON_Parse(json);
    cJSON *id = cJSON_GetObjectItem(root, "id");
    cJSON *username = cJSON_GetObjectItem(root, "username");
    cJSON *password = cJSON_GetObjectItem(root, "password");
    UserInfo *user = userInfoInit(id->valuestring, username->valuestring, password->valuestring);
    cJSON_Delete(root);
    return user;
}
char *userInfoToJsonString(UserInfo *user) {
    char *result;
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "id", user->id);
    cJSON_AddStringToObject(root, "username", user->username);
    cJSON_AddStringToObject(root, "password", user->password);
    result = cJSON_Print(root);
    cJSON_Delete(root);
    return result;
}
void userInfoFree(UserInfo *user) {
    if (user->id != NULL) {
        free(user->id);
        user->id = NULL;
    }
    if (user->username != NULL) {
        free(user->username);
        user->username = NULL;
    }
    if (user->password != NULL) {
        free(user->password);
        user->password = NULL;
    }
    free(user);
}
