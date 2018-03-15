//
//  data_error.h
//  server
//
//  Created by Mingle on 2018/3/15.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#ifndef data_error_h
#define data_error_h

#include <stdio.h>
//PROTOCOL_TYPE_ERROR 错误数据结构
struct data_error {
    uint32_t code;
    uint32_t type;
    char *msg;
    char *local_msg;
};
typedef struct data_error Data_error;

Data_error *dataErrorInit(uint32_t code, uint32_t type, char *msg, char *local_msg);
Data_error *dataErrorFromJsonString(char *json);
char *dataErrorToJsonString(Data_error *data_error);
void dataErrorFree(Data_error *data_error);

#endif /* data_error_h */
