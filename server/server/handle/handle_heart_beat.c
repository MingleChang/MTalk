//
//  handle_heart_beat.c
//  server
//
//  Created by Mingle on 2018/3/15.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "handle_heart_beat.h"
#include "server.h"

int handleHeartBeat(struct base_socket *socket) {
    socket->heartbeat = HEART_BEAT;
    return 0;
}
