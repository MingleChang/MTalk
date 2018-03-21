//
//  handle_error_recv.c
//  client
//
//  Created by Mingle on 2018/3/15.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "handle_error_recv.h"
#include "client.h"

void handle_error_recv(struct protocol head, void *data) {
    char *value = (char *)data;
    Data_error *error = dataErrorFromJsonString(value);
    err_msg("Error=>Code:%ld, Message:%s", error->code, error->msg);
    dataErrorFree(error);
}
