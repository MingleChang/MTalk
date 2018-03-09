//
//  fd_queue.h
//  server
//
//  Created by Mingle on 2018/3/9.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#ifndef fd_queue_h
#define fd_queue_h

#include <stdlib.h>
#include <stdio.h>

int Fd_queue_init(void);
void Fd_queue_add_event(int fq, int fd, uint8_t event);
void Fd_queue_delete_event(int fq, int fd, uint8_t event);

#endif /* fd_queue_h */
