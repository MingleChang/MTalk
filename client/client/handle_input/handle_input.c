//
//  handle_input.c
//  client
//
//  Created by Mingle on 2018/3/15.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "handle_input.h"
#include "client.h"
#include "handle_test_input.h"
#include "handle_login_input.h"
#include "handle_user_list_input.h"
#include "handle_send_input.h"
#include "handle_logout_input.h"

void handle_input(char *input) {
    char *value = input;
    char *sep = " ";
    char *command = strsep(&value, sep);
    if (strcmp(command, "test") == 0) {
        handle_test_input(value);
    }
    if (strcmp(command, "login") == 0) {
        handle_login_input(value);
    }
    if (strcmp(command, "logout\n") == 0) {
        handle_logout_input(value);
    }
    if (strcmp(command, "userlist\n") == 0) {
        handle_user_list_input(value);
    }
    if (strcmp(command, "send") == 0) {
        handle_send_input(value);
    }
}

void Handle_input(char *input) {
    handle_input(input);
}
