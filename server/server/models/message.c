//
//  message.c
//  server
//
//  Created by Mingle on 2018/3/22.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "message.h"
#include "cJSON.h"
#include <stdlib.h>
#include <string.h>

Message *messageInit(char *id, uint32_t type, char *from, char *to, char *value) {
    Message *message = malloc(sizeof(Message));
    size_t length;
    
    length = strlen(id) + 1;
    message->id = (char *)malloc(length);
    memset(message->id, 0, length);
    strcpy(message->id, id);
    message->id[length] = '\0';
    
    message->type = type;
    
    length = strlen(from) + 1;
    message->from = (char *)malloc(length);
    memset(message->from, 0, length);
    strcpy(message->from, from);
    message->from[length] = '\0';
    
    length = strlen(to) + 1;
    message->to = (char *)malloc(length);
    memset(message->to, 0, length);
    strcpy(message->to, to);
    message->to[length] = '\0';
    
    length = strlen(value) + 1;
    message->value = (char *)malloc(length);
    memset(message->value, 0, length);
    strcpy(message->value, value);
    message->value[length] = '\0';
    return message;
}
Message *messageFromJsonString(char *json) {
    cJSON *root = cJSON_Parse(json);
    cJSON *id = cJSON_GetObjectItem(root, "id");
    cJSON *type = cJSON_GetObjectItem(root, "type");
    cJSON *from = cJSON_GetObjectItem(root, "from");
    cJSON *to = cJSON_GetObjectItem(root, "to");
    cJSON *value = cJSON_GetObjectItem(root, "value");
    Message *message = messageInit(id->valuestring, type->valueint, from->valuestring, to->valuestring, value->valuestring);
    cJSON_Delete(root);
    return message;
}
char *messageToJsonString(Message *message) {
    char *result;
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "id", message->id);
    cJSON_AddNumberToObject(root, "type", message->type);
    cJSON_AddStringToObject(root, "from", message->from);
    cJSON_AddStringToObject(root, "to", message->to);
    cJSON_AddStringToObject(root, "value", message->value);
    result = cJSON_Print(root);
    cJSON_Delete(root);
    return result;
}
void messageFree(Message *message) {
    if (message->id != NULL) {
        free(message->id);
        message->id = NULL;
    }
    if (message->from != NULL) {
        free(message->from);
        message->from = NULL;
    }
    if (message->to != NULL) {
        free(message->to);
        message->to = NULL;
    }
    if (message->value != NULL) {
        free(message->value);
        message->value = NULL;
    }
    free(message);
}
