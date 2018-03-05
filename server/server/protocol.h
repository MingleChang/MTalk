//
//  protocol.h
//  server
//
//  Created by Mingle on 2018/3/1.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#ifndef protocol_h
#define protocol_h

#include <stdio.h>

#define PROTOCOL_VERSION 0x0001
#define PROTOCOL_AUTH 0x2435

struct protocol_head {
    uint16_t version;   //协议版本号
    uint16_t auth;      //认证
    uint32_t no;        //序号
    uint32_t type;      //类型
    uint32_t length;    //数据长度
};

struct protocol_data {
    struct protocol_head head;
    void *data;
};

typedef struct protocol_head Protocol_head;
typedef struct protocol_data Protocol_data;

#endif /* protocol_h */
