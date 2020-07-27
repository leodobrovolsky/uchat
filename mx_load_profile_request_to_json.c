#include "uchat.h"

char *mx_load_profile_request_to_json(char *user) {
    char *tmp = mx_file_to_str(LOAD_PROFILE_REQUEST_FILE);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&time", times);
    mx_replace_str(&tmp, "&user", user);
    mx_strdel(&times);
    return tmp;
}
