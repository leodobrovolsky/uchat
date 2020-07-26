#include "uchat.h"

char *mx_connect_response_to_json(int status) {
    char *tmp = mx_file_to_str(CONNECT_RESPONSE_FILE);
    char *times = mx_get_current_time();
    char *st = mx_itoa(status);

    mx_replace_str(&tmp, "&time", times);
    mx_replace_str(&tmp, "&status", st); 
    mx_strdel(&times);
    mx_strdel(&st);
    return tmp;   
}
