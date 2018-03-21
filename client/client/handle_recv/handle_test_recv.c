//
//  handle_test_recv.c
//  client
//
//  Created by Mingle on 2018/3/15.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "handle_test_recv.h"
#include "client.h"

void handle_test_recv(struct protocol head, void *data) {
    char *value = (char *)data;
    err_msg("Test=>%s", value);
}
