//
//  send_data.h
//  server
//
//  Created by Mingle on 2018/3/14.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#ifndef send_data_h
#define send_data_h

#include <stdio.h>
#include "protocol.h"

void Send_data(int fd, struct protocol *head, char *data);

#endif /* send_data_h */
