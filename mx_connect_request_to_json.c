#include "uchat.h"

char *mx_connect_request_to_json() {
    char *tmp = mx_file_to_str(CONNECT_REQUEST_FILE);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&time", times); 
    mx_strdel(&times);
    return tmp;
}
