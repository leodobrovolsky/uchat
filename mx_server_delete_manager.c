#include "uchat.h"

void mx_server_delete_manager() {
    char *manager = mx_strnew(SERVER_INPUT_SIZE);
    t_list_arr *res = NULL;
    t_database db;
    t_table *table = NULL;
    char *condition = NULL;
    char *check = mx_strnew(SERVER_INPUT_SIZE);

    mx_printstr("Введите логин менеджера-> ");
    mx_getch(manager);
    db.name_db = DATABASE_NAME;
    db.name_table = "users";
    mx_push_t_table(&table, "login", NULL, "TEXT");
    db.table = table;
    condition = mx_strjoin("WHERE login ='", manager);
    mx_stradd(&condition, "';");
    res = mx_select_table(db, condition, 1);
    if (res) {
        mx_printstr("Удалить менеджера ");
        mx_printstr(manager);
        mx_printstr(" y/n ? ");
        mx_getch(check);
        if (!mx_strcmp(check, "y")) {
            mx_delete_data(db, condition);
            mx_printstr("Менеджер удален!\n");
        }
    }
    else
        mx_printstr("Менеджер не найден!\n");
    mx_free_t_table(&db.table);
    mx_strdel(&condition);
    mx_strdel(&check);
}
