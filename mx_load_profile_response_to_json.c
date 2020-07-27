#include "uchat.h"

char *mx_load_profile_response_to_json(t_user_create user, int status) {
    char *tmp = mx_file_to_str(LOAD_PROFILE_RESPONSE_FILE);
    char *st = mx_itoa(status);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&time", times);
    mx_replace_str(&tmp, "&status", st);
    mx_replace_str(&tmp, "&login", user.login);
    mx_replace_str(&tmp, "&name", user.name);
    mx_replace_str(&tmp, "&surname", user.surname);
    mx_replace_str(&tmp, "&email", user.email);
    mx_replace_str(&tmp, "&rules", user.rules);
    mx_replace_str(&tmp, "&user_status", user.status);
    mx_strdel(&times);
    mx_strdel(&st);
    return tmp;
}
