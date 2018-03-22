//
//  handle_logout_recv.c
//  client
//
//  Created by Mingle on 2018/3/22.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "handle_logout_recv.h"
#include "client.h"

void handle_logout_recv(struct protocol head, void *data) {
    err_msg("logout Success");
    free(user_id);
    user_id = NULL;
}
