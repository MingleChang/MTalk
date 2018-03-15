//
//  login_request.c
//  server
//
//  Created by Mingle on 2018/3/15.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "login_request.h"
#include "cJSON.h"
#include <stdlib.h>
#include <string.h>

Login_request *loginRequestInit(char *username, char *password) {
    Login_request *request = malloc(sizeof(Login_request));
    size_t length;
    length = strlen(username) + 1;
    request->username = (char *)malloc(length);
    memset(request->username, 0, length);
    strcpy(request->username, username);
    request->username[length] = '\0';
    length = strlen(password) + 1;
    request->password = (char *)malloc(length);
    memset(request->password, 0, length);
    strcpy(request->password, password);
    request->password[length] = '\0';
    return request;
}

Login_request *loginRequestFromJsonString(char *json) {
    cJSON *root = cJSON_Parse(json);
    cJSON *username = cJSON_GetObjectItem(root, "username");
    cJSON *password = cJSON_GetObjectItem(root, "password");
    Login_request *request = loginRequestInit(username->valuestring, password->valuestring);
    cJSON_Delete(root);
    return request;
}

char *loginRequestToJsonString(Login_request *request) {
    char *result;
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "username", request->username);
    cJSON_AddStringToObject(root, "password", request->password);
    result = cJSON_Print(root);
    cJSON_Delete(root);
    return result;
}
void loginRequestFree(Login_request *request) {
    if (request->username != NULL) {
        free(request->username);
        request->username = NULL;
    }
    if (request->password != NULL) {
        free(request->password);
        request->password = NULL;
    }
    free(request);
}
