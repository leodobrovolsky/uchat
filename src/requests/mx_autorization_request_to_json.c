#include "uchat.h"

char *mx_autorization_request_to_json(char *login, char *passwd) {
    char *tmp = mx_file_to_str(AUTORIZATION_REQUEST_FILE);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&time", times);
    mx_replace_str(&tmp, "&login", login);
    mx_replace_str(&tmp, "&password", passwd);
    mx_strdel(&times);
    return tmp;
}
