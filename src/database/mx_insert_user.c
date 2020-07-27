#include "uchat.h"

static char **mx_insert_user2(t_user_create *user) {
    char **user_arr = mx_create_char_arr(TABLE_USERS_COLUMNS);

    user_arr[0] = mx_strdup("NULL");
    user_arr[1] = mx_strdup(user->login);
    user_arr[2] = mx_strdup(user->password);
    user_arr[3] = mx_strdup(user->name);
    user_arr[4] = mx_strdup(user->surname);
    user_arr[5] = mx_strdup(user->email);
    user_arr[6] = mx_strdup(user->rules);
    user_arr[7] = mx_strdup("active");
    return user_arr;
}



bool mx_insert_user(t_user_create *user) {
    t_table *table = mx_create_t_table_users();
    t_database db;
    char **user_arr = mx_insert_user2(user);
    char **unique = mx_create_char_arr(2);

    unique[0] = mx_strdup("login");
    unique[1] = mx_strdup(user->login);
    db.name_db = DATABASE_NAME;
    db.name_table = TABLE_NAME_USERS;
    mx_push_data_table(&table, user_arr);
    db.table = table;
    if (!mx_check_unique_update_data(db, unique, TABLE_USERS_COLUMNS)) {
        mx_del_strarr(&unique);
        mx_insert_data(db);
        mx_free_t_table(&db.table);
        return true;
    }

    mx_free_t_table(&db.table);
    mx_del_strarr(&unique);
    return false;
}
