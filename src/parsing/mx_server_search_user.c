#include "uchat.h"

t_list_arr *mx_server_search_user(char *login, char *password) {
    t_list_arr *res = NULL;
    t_database db;
    char *cond = mx_strdup("WHERE login = '");

    db.name_db = DATABASE_NAME;
    db.name_table = TABLE_NAME_USERS;
    db.table = mx_create_t_table_users();
    mx_stradd(&cond, login);
    mx_stradd(&cond, "' AND password = '");
    mx_stradd(&cond, password);
    mx_stradd(&cond, "' AND status = '");
    mx_stradd(&cond, USER_STATUS_ACTIVE);
    mx_stradd(&cond, "'");
    res = mx_select_table(db, cond, TABLE_USERS_COLUMNS);
    mx_strdel(&cond);
    mx_free_t_table(&db.table);
    return res;
}
