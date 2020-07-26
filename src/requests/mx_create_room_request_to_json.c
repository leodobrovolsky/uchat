#include "uchat.h"

char *mx_create_room_request_to_json(char *name) {
    char *tmp = mx_file_to_str(CREATE_ROOM_REQUEST_FILE);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&time", times);
    mx_replace_str(&tmp, "&name", name);
    mx_strdel(&times);
    return tmp;
}
