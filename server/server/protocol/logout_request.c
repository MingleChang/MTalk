//
//  logout_request.c
//  server
//
//  Created by Mingle on 2018/3/15.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "logout_request.h"
#include "cJSON.h"
#include <stdlib.h>
#include <string.h>

Logout_request *logoutRequestInit(char *user_id) {
    Logout_request *request = malloc(sizeof(Logout_request));
    size_t length = strlen(user_id) + 1;
    request->user_id = (char *)malloc(length);
    memset(request->user_id, 0, length);
    strcpy(request->user_id, user_id);
    request->user_id[length] = '\0';
    return request;
}
Logout_request *logoutRequestFromJsonString(char *json) {
    cJSON *root = cJSON_Parse(json);
    cJSON *user_id = cJSON_GetObjectItem(root, "user_id");
    Logout_request *request = logoutRequestInit(user_id->valuestring);
    cJSON_Delete(root);
    return request;
}
char *logoutRequestToJsonString(Logout_request *request) {
    char *result;
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "user_id", request->user_id);
    result = cJSON_Print(root);
    cJSON_Delete(root);
    return result;
}
void logoutRequestFree(Logout_request *request) {
    if (request->user_id != NULL) {
        free(request->user_id);
        request->user_id = NULL;
    }
    free(request);
}
