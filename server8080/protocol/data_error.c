//
//  data_error.c
//  server
//
//  Created by Mingle on 2018/3/15.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "data_error.h"
#include "cJSON.h"
#include <stdlib.h>
#include <string.h>

Data_error *dataErrorInit(uint32_t code, uint32_t type, char *msg, char *local_msg) {
    Data_error *error = malloc(sizeof(Data_error));
    error->code = code;
    error->type = type;
    size_t length;
    length = strlen(msg) + 1;
    error->msg = (char *)malloc(length);
    memset(error->msg, 0, length);
    strcpy(error->msg, msg);
    length = strlen(local_msg) + 1;
    error->local_msg = (char *)malloc(length);
    memset(error->local_msg, 0, length);
    strcpy(error->local_msg, local_msg);
    return error;
}
Data_error *dataErrorFromJsonString(char *json) {
    cJSON *root = cJSON_Parse(json);
    cJSON *code = cJSON_GetObjectItem(root, "code");
    cJSON *type = cJSON_GetObjectItem(root, "type");
    cJSON *msg = cJSON_GetObjectItem(root, "msg");
    cJSON *local_msg = cJSON_GetObjectItem(root, "local_msg");
    Data_error *error = dataErrorInit(code->valueint, type->valueint, msg->valuestring, local_msg->valuestring);
    cJSON_Delete(root);
    return error;
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
