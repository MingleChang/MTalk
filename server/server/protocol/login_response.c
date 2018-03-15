//
//  login_response.c
//  server
//
//  Created by Mingle on 2018/3/15.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "login_response.h"
#include "cJSON.h"
#include <stdlib.h>
#include <string.h>

Login_response *loginResponseInit(char *user_id) {
    Login_response *response = malloc(sizeof(Login_response));
    size_t length = strlen(user_id) + 1;
    response->user_id = (char *)malloc(length);
    memset(response->user_id, 0, length);
    strcpy(response->user_id, user_id);
    response->user_id[length] = '\0';
    return response;
}
Login_response *loginResponseFromJsonString(char *json) {
    cJSON *root = cJSON_Parse(json);
    cJSON *user_id = cJSON_GetObjectItem(root, "user_id");
    Login_response *response = loginResponseInit(user_id->valuestring);
    cJSON_Delete(root);
    return response;
}
char *loginResponseToJsonString(Login_response *response) {
    char *result;
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "user_id", response->user_id);
    result = cJSON_Print(root);
    cJSON_Delete(root);
    return result;
}
void loginResponseFree(Login_response *response) {
    if (response->user_id) {
        free(response->user_id);
        response->user_id = NULL;
    }
    free(response);
}
