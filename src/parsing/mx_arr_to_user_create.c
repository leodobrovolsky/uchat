#include "uchat.h"

t_user_create *mx_arr_to_user_create(char **arr) {
    t_user_create *user = NULL;

    if (mx_arr_size(arr) < TABLE_USERS_COLUMNS)
        return NULL;
    user = malloc(sizeof(t_user_create));
    user->id = mx_strdup(arr[0]);
    user->login = mx_strdup(arr[1]);
    user->password = mx_strdup(arr[2]);
    user->name = mx_strdup(arr[3]);
    user->surname = mx_strdup(arr[4]);
    user->email = mx_strdup(arr[5]);
    user->rules = mx_strdup(arr[6]);
    user->status = mx_strdup(arr[7]);
    return user;
}
