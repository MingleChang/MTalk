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

//协议类型定义
//错误
#define PROTOCOL_TYPE_ERROR 0x0000
//测试协议，数据后群发data数据
#define PROTOCOL_TYPE_TEST 0x0001
//心跳
#define PROTOCOL_TYPE_HEART_BEAT 0x000f
//登录
#define PROTOCOL_TYPE_LOGIN_REQ 0x0010
#define PROTOCOL_TYPE_LOGIN_RES 0x0011
//注册
#define PROTOCOL_TYPE_REGISTER_REQ 0x0012
#define PROTOCOL_TYPE_REGISTER_RES 0x0013
//退出
#define PROTOCOL_TYPE_LOGOUT_REQ 0x0014
#define PROTOCOL_TYPE_LOGOUT_RES 0x0015
//用户信息
#define PROTOCOL_TYPE_USER_INFO_REQ 0x0016
#define PROTOCOL_TYPE_USER_INFO_RES 0x0017
//用户列表
#define PROTOCOL_TYPE_USER_LIST_REQ 0x0018
#define PROTOCOL_TYPE_USER_LIST_RES 0x0019
//发送消息
#define PROTOCOL_TYPE_SEND_MSG_REQ 0x0100
#define PROTOCOL_TYPE_SEND_MSG_RES 0x0101

struct protocol {
    uint16_t version;   //协议版本号：PROTOCOL_VERSION，用于兼容
    uint16_t auth;      //认证：PROTOCOL_AUTH，如果不为PROTOCOL_AUTH则说明不符合协议规范
    uint32_t no;        //序号：当前发送数据编号
    uint32_t type;      //类型：数据类型定义
    uint32_t length;    //数据长度
};
typedef struct protocol Protocol;

//PROTOCOL_TYPE_ERROR 错误数据结构
struct data_error {
    uint32_t code;
    uint32_t type;
    char *msg;
    char *local_msg;
};
typedef struct data_error Data_error;

Data_error *dataErrorFromJsonString(char *json);
char *dataErrorToJsonString(Data_error *data_error);
void dataErrorFree(Data_error *data_error);

struct login_request {
    char *username;
    char *password;
};
typedef struct login_request Login_request;
Login_request *loginRequestFromJsonString(char *json);
char *loginRequestToJsonString(Login_request *request);
void loginRequestFree(Login_request *request);

struct login_response {
    char *user_id;//创建一个用户id返回
};
typedef struct login_response Login_response;
Login_response *loginResponseFromJsonString(char *json);
char *loginResponseToJsonString(Login_response *response);
void loginResponseFree(Login_response *response);

#endif /* protocol_h */
