#include "uchat.h"

static void mx_get_new_user_data(char *type, char **tmp, char *data) {
    mx_strdel(tmp);
    *tmp = mx_strnew(SERVER_INPUT_SIZE);
    mx_printstr("Изменить ");
    mx_printstr(type);
    mx_printstr(" c ");
    mx_printstr(data);
    mx_printstr(" на-> ");
    mx_getch(*tmp);
}

void mx_server_edit_manager() {
    char *tmp = mx_strnew(SERVER_INPUT_SIZE);
    t_database db;
    char **check_unique = mx_create_char_arr(2);
    t_list_arr *old_data = NULL;
    char *cond = mx_strdup("WHERE login = \'");
    t_user_create *user = malloc(sizeof(t_user_create));  
    char *old_login = NULL;

    check_unique[0] = mx_strdup("login");
    db.name_db = DATABASE_NAME;
    db.name_table = TABLE_NAME_USERS;
    db.table = mx_create_t_table_users();
    mx_printstr("Введите логин менеджера-> ");
    mx_getch(tmp);
    old_login = mx_strdup(tmp);
    mx_stradd(&cond, tmp);
    mx_stradd(&cond, "\'");
    old_data = mx_select_table(db, cond, TABLE_USERS_COLUMNS); 

    if (!old_data) {
        mx_printstr("Менеджер не найден!\n");
        mx_del_strarr(&check_unique);
        mx_free_t_table(&db.table);
        mx_strdel(&tmp);
        return;
    }
    mx_get_new_user_data("логин", &tmp, old_data->data[1]);
    user->login = mx_strdup(tmp);
    check_unique[1] = mx_strdup(tmp);
    if (mx_check_unique_update_data(db, check_unique, TABLE_USERS_COLUMNS)) {
        mx_printstr("Менеджер с таким логином уже существует!\n");
        mx_del_strarr(&check_unique);
        mx_free_t_table(&db.table);
        mx_strdel(&tmp);
        mx_strdel(&old_login);
        return;
    }
    mx_get_new_user_data("пароль", &tmp, old_data->data[2]);
    user->password = mx_strdup(tmp);
    mx_get_new_user_data("имя", &tmp, old_data->data[3]);
    user->name = mx_strdup(tmp);
    mx_get_new_user_data("фамилию", &tmp, old_data->data[4]);
    user->surname = mx_strdup(tmp);
    mx_get_new_user_data("email", &tmp, old_data->data[5]);
    user->email = mx_strdup(tmp);
    user->rules = mx_strdup("manager");
    user->status = mx_strdup("active");
    mx_print_user_create(user);
    mx_printstr("\nСохранить: y/n ? ");
    mx_strdel(&tmp);
    tmp = mx_strnew(SERVER_INPUT_SIZE);
    mx_getch(tmp);

    if (!mx_strcmp(tmp, "y"))
        mx_update_user(user, old_login);
    mx_free_user_create(&user);
    mx_free_t_table(&db.table);
    mx_strdel(&tmp);
    mx_del_strarr(&check_unique);
    mx_free_arr_list(&old_data);
    mx_strdel(&cond);
    mx_strdel(&old_login);
}
