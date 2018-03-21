//
//  user_list_request.c
//  server
//
//  Created by Mingle on 2018/3/15.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "user_list_request.h"
#include "cJSON.h"
#include <stdlib.h>
#include <string.h>

User_list_request *userListRequestInit(char *user_id) {
    User_list_request *request = malloc(sizeof(User_list_request));
    size_t length = strlen(user_id) + 1;
    request->user_id = (char *)malloc(length);
    memset(request->user_id, 0, length);
    strcpy(request->user_id, user_id);
    request->user_id[length] = '\0';
    return request;
}
User_list_request *userListRequestFromJsonString(char *json) {
    cJSON *root = cJSON_Parse(json);
    cJSON *user_id = cJSON_GetObjectItem(root, "user_id");
    User_list_request *request = userListRequestInit(user_id->valuestring);
    cJSON_Delete(root);
    return request;
}
char *userListRequestToJsonString(User_list_request *request) {
    char *result;
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "user_id", request->user_id);
    result = cJSON_Print(root);
    cJSON_Delete(root);
    return result;
}
void userListRequestFree(User_list_request *request) {
    if (request->user_id != NULL) {
        free(request->user_id);
        request->user_id = NULL;
    }
    free(request);
}
