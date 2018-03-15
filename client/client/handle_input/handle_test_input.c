//
//  handle_test_input.c
//  client
//
//  Created by Mingle on 2018/3/15.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "handle_test_input.h"
#include "client.h"

void handle_test_input(char *data) {
    char *value = data;
    if (value == NULL) {
        err_msg("test [string]");
        return;
    }
    Protocol head;
    head.version = PROTOCOL_VERSION;
    head.auth = PROTOCOL_AUTH;
    head.type = PROTOCOL_TYPE_TEST;
    head.length = (uint32_t)strlen(value) + 1;
    send_output(head, value);
}
