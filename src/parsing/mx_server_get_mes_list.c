#include "uchat.h"

t_list_arr *mx_server_get_mes_list(char *name) {
    t_list_arr *res = NULL;
    char *cond = mx_strdup("WHERE room_id = ");
    t_database db;

    db.name_db = DATABASE_NAME;
    db.name_table = TABLE_NAME_MESSAGES;
    db.table = mx_create_t_table_messages();
    mx_stradd(&cond, mx_get_room_id(name));
    res = mx_select_table(db, cond, TABLE_MESSAGES_COLUMNS);
    mx_strdel(&cond);
    mx_free_t_table(&db.table);
    return res;
}
