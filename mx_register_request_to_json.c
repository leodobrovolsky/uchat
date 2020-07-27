#include "uchat.h"

char *mx_register_request_to_json(t_user_create user) {
    char *tmp = mx_file_to_str(REGISTER_REQUEST_FILE);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&time", times);
    mx_replace_str(&tmp, "&login", user.login);
    mx_replace_str(&tmp, "&password", user.password);
    mx_replace_str(&tmp, "&name", user.name);
    mx_replace_str(&tmp, "&surname", user.surname);
    mx_replace_str(&tmp, "&email", user.email);
    mx_strdel(&times);
    return tmp;
}
