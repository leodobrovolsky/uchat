#include "uchat.h"

t_list_arr *mx_get_select(char *table, char *cond) {
    t_list_arr *res = NULL;
    t_database db;
    int column = 0;

    db.name_db = DATABASE_NAME;
    if (!mx_strcmp(table, TABLE_NAME_USERS)) {
        db.name_table = TABLE_NAME_USERS;
        db.table = mx_create_t_table_users();
        column = TABLE_USERS_COLUMNS;
    }
    else if (!mx_strcmp(table, TABLE_NAME_ROOMS)) {
        db.name_table = TABLE_NAME_ROOMS;
        db.table = mx_create_t_table_users();
        column = TABLE_ROOMS_COLUMNS;
    }
    else if (!mx_strcmp(table, TABLE_NAME_USERS_ROOMS)) {
        db.name_table = TABLE_NAME_USERS_ROOMS;
        db.table = mx_create_t_table_users();
        column = TABLE_USERS_ROOMS_COLUMNS;
    }
    else if (!mx_strcmp(table, TABLE_NAME_MESSAGES)) {
        db.name_table = TABLE_NAME_MESSAGES;
        db.table = mx_create_t_table_users();
        column = TABLE_MESSAGES_COLUMNS;
    }
    else if (!mx_strcmp(table, TABLE_NAME_ACTIVE_USERS)) {
        db.name_table = TABLE_NAME_ACTIVE_USERS;
        db.table = mx_create_t_table_users();
        column = TABLE_ACTIVE_USERS_COLUMNS;
    }
    else
        return NULL;
    res = mx_select_table(db, cond, column);
    mx_free_t_table(&db.table);
    return res;
}
