#include "uchat.h"

void mx_server_managers() {
    t_table *table = NULL;
    t_list_arr *arr = NULL;
    t_database db;
    char *condition = NULL;

    db.name_db = DATABASE_NAME;
    db.name_table = TABLE_NAME_USERS;
    table = mx_create_t_table_users();
    db.table = table;
    arr = mx_select_table(db, "WHERE rules = 'manager'", 5);
    mx_print_list_arr(arr);
    mx_free_arr_list(&arr);
    mx_free_t_table(&table);
    mx_strdel(&condition);
}
