//
//  handle_test.c
//  server
//
//  Created by Mingle on 2018/3/15.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "server.h"

//处理PROTOCOL_TYPE_TEST类型数据
int handleTest(Base_socket *socket) {
    Base_socket *con_socket = base_socket_list->next;
    while (con_socket != NULL) {
        Send_data(con_socket->fd, socket->head, socket->data_buff);
        con_socket = con_socket->next;
    }
    return 0;
}
