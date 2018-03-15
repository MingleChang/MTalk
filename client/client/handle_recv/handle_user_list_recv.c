//
//  handle_user_list_recv.c
//  client
//
//  Created by Mingle on 2018/3/15.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "handle_user_list_recv.h"
#include "client.h"

void handle_user_list_recv(Protocol head, void *data) {
    char *json = (char *)data;
    cJSON *root = cJSON_Parse(json);
    if (root->type != cJSON_Array) {
        cJSON_Delete(root);
        return;
    }
    int n = cJSON_GetArraySize(root);
    for (int i = 0; i < n; i++) {
        cJSON *item = cJSON_GetArrayItem(root, i);
        err_msg("%s", item->valuestring);
    }
}
