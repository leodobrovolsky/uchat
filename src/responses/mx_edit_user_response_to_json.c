#include "uchat.h"

char *mx_edit_user_response_to_json(int status) {
    char *tmp = mx_file_to_str(EDIT_USER_RESPONSE_FILE);
    char *st = mx_itoa(status);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&time", times);
    mx_replace_str(&tmp, "&status", st);
    mx_strdel(&times);
    mx_strdel(&st);
    return tmp;   
}
