//
//  send_msg_request.c
//  server
//
//  Created by Mingle on 2018/3/15.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "send_msg_request.h"
#include "cJSON.h"
#include <stdlib.h>
#include <string.h>

Send_msg_request *sendMsgRequestInit(uint32_t type, char *from_user, char *to_user, char *message) {
    Send_msg_request *request = malloc(sizeof(Send_msg_request));
    size_t length;
    length = strlen(from_user) + 1;
    request->from_user = (char *)malloc(length);
    memset(request->from_user, 0, length);
    strcpy(request->from_user, from_user);
    request->from_user[length] = '\0';
    
    length = strlen(to_user) + 1;
    request->to_user = (char *)malloc(length);
    memset(request->to_user, 0, length);
    strcpy(request->to_user, to_user);
    request->to_user[length] = '\0';
    
    length = strlen(message) + 1;
    request->message = (char *)malloc(length);
    memset(request->message, 0, length);
    strcpy(request->message, message);
    request->message[length] = '\0';
    return request;
}
Send_msg_request *sendMsgRequestFromJsonString(char *json) {
    cJSON *root = cJSON_Parse(json);
    cJSON *type = cJSON_GetObjectItem(root, "type");
    cJSON *from_user = cJSON_GetObjectItem(root, "from_user");
    cJSON *to_user = cJSON_GetObjectItem(root, "to_user");
    cJSON *message = cJSON_GetObjectItem(root, "message");
    Send_msg_request *request = sendMsgRequestInit(type->valueint, from_user->valuestring, to_user->valuestring, message->valuestring);
    cJSON_Delete(root);
    return request;
}
char *sendMsgRequestToJsonString(Send_msg_request *request) {
    char *result;
    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "type", request->type);
    cJSON_AddStringToObject(root, "from_user", request->from_user);
    cJSON_AddStringToObject(root, "to_user", request->to_user);
    cJSON_AddStringToObject(root, "message", request->message);
    result = cJSON_Print(root);
    cJSON_Delete(root);
    return result;
}
void sendMsgRequestFree(Send_msg_request *request) {
    if (request->from_user != NULL) {
        free(request->from_user);
        request->from_user = NULL;
    }
    if (request->to_user != NULL) {
        free(request->to_user);
        request->to_user = NULL;
    }
    if (request->message != NULL) {
        free(request->message);
        request->message = NULL;
    }
    free(request);
}
