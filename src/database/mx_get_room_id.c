#include "uchat.h"

char *mx_get_room_id(char *name) {
    t_database db;
    t_list_arr *res = NULL;
    char *cond = mx_strdup("WHERE name = '");
    char *room_id = NULL;

    db.name_db = DATABASE_NAME;
    db.name_table = TABLE_NAME_ROOMS;
    db.table = mx_create_t_table_rooms();
    mx_stradd(&cond, name);
    mx_stradd(&cond, "'");
    res = mx_select_table(db, cond, TABLE_ROOMS_COLUMNS);
    if(res)
        room_id = mx_strdup(res->data[0]);
    mx_strdel(&cond);
    mx_free_arr_list(&res);
    mx_free_t_table(&db.table);
    return room_id;
}
