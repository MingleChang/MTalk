//
//  database.c
//  server
//
//  Created by Mingle on 2018/3/22.
//  Copyright © 2018年 Mingle. All rights reserved.
//

#include "database.h"
#include <sqlite3.h>

static sqlite3 *db;

int db_init(void) {
    int result = sqlite3_open("/mtalk.sqlite", &db);
    return result;
}

int db_init_table(void) {
    return 0;
}
