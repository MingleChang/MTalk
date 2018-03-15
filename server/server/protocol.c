//
//  protocol.c
//  server
//
//  Created by Mingle on 2018/3/1.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "protocol.h"
#include "cJSON/cJSON.h"
#include <stdlib.h>
#include <string.h>

Data_error *dataErrorFromJsonString(char *json) {
    Data_error *data_error = malloc(sizeof(Data_error));
    cJSON *root = cJSON_Parse(json);
    cJSON *code = cJSON_GetObjectItem(root, "code");
    cJSON *type = cJSON_GetObjectItem(root, "type");
    cJSON *msg = cJSON_GetObjectItem(root, "msg");
    cJSON *local_msg = cJSON_GetObjectItem(root, "local_msg");
    data_error->code = code->valueint;
    data_error->type = type->valueint;
    data_error->msg = (char *)malloc(strlen(msg->valuestring));
    strcat(data_error->msg, msg->valuestring);
    data_error->local_msg = (char *)malloc(strlen(local_msg->valuestring));
    strcat(data_error->local_msg, local_msg->valuestring);
    cJSON_Delete(root);
    return data_error;
}
char *dataErrorToJsonString(Data_error *data_error) {
    char *result;
    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "code", data_error->code);
    cJSON_AddNumberToObject(root, "type", data_error->type);
    cJSON_AddStringToObject(root, "msg", data_error->msg);
    cJSON_AddStringToObject(root, "local_msg", data_error->local_msg);
    result = cJSON_Print(root);
    cJSON_Delete(root);
    return result;
}
void dataErrorFree(Data_error *data_error) {
    if (data_error->msg != NULL) {
        free(data_error->msg);
        data_error->msg = NULL;
    }
    if (data_error->local_msg != NULL) {
        free(data_error->local_msg);
        data_error->local_msg = NULL;
    }
    free(data_error);
}


Login_request *loginRequestFromJsonString(char *json) {
    Login_request *request = malloc(sizeof(Login_request));
    cJSON *root = cJSON_Parse(json);
    cJSON *username = cJSON_GetObjectItem(root, "username");
    cJSON *password = cJSON_GetObjectItem(root, "password");
    request->username = (char *)malloc(strlen(username->valuestring));
    strcat(request->username, username->valuestring);
    request->password = (char *)malloc(strlen(password->valuestring));
    strcat(request->password, password->valuestring);
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


Login_response *loginResponseFromJsonString(char *json) {
    Login_response *response = malloc(sizeof(Login_response));
    cJSON *root = cJSON_Parse(json);
    cJSON *user_id = cJSON_GetObjectItem(root, "user_id");
    response->user_id = (char *)malloc(strlen(user_id->valuestring));
    strcat(response->user_id, user_id->valuestring);
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

