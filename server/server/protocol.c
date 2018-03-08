//
//  protocol.c
//  server
//
//  Created by Mingle on 2018/3/1.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "protocol.h"
#include "server.h"

#pragma mark - Data error
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
