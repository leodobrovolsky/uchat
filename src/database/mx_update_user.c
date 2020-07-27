#include "uchat.h"

static void mx_free_update_user(t_table **t, char ***c_k, char **cond, char ***u_a) {
    mx_del_strarr(c_k);
    mx_free_t_table(t);
    mx_strdel(cond);
    mx_del_strarr(u_a);
}

char **mx_user_create_to_char_arr(t_user_create *user) {
    char **tmp = mx_create_char_arr(TABLE_USERS_COLUMNS - 1);

    //tmp[0] = mx_get_user_id(user->login);
    tmp[0] = mx_strdup(user->login);
    tmp[1] = mx_strdup(user->password); 
    tmp[2] = mx_strdup(user->name);
    tmp[3] = mx_strdup(user->surname); 
    tmp[4] = mx_strdup(user->email);
    tmp[5] = mx_strdup(user->rules);
    tmp[6] = mx_strdup(user->status);
    return tmp;
}

bool mx_update_user(t_user_create *user, char *old_login) {
    t_database db;
    char *cond = mx_strdup("WHERE login = \'");
    char **check_unique = mx_create_char_arr(2);
    char **user_arr = mx_user_create_to_char_arr(user);

    db.name_db = DATABASE_NAME;
    db.name_table = TABLE_NAME_USERS;
    db.table = mx_create_t_table_users();
    mx_pop_front_table(&db.table);
    mx_push_data_table(&db.table, user_arr); 
    check_unique[0] = mx_strdup("login");
    check_unique[1] = mx_strdup(user->login); 
    mx_stradd(&cond, old_login);
    mx_stradd(&cond, "\'");
    if (mx_check_unique_update_data(db, check_unique, TABLE_USERS_COLUMNS)) {
        //mx_free_update_user(&db.table, &check_unique, &cond, &user_arr);
        return false;
    }
    mx_update_data(db, cond);
    //mx_free_update_user(&db.table, &check_unique, &cond, &user_arr);
    return true;
}
