#include "uchat.h"

char *mx_leav_room_request_to_json(char *room, char *user) {
    char *tmp = mx_file_to_str(LEAV_ROOM_REQUEST_FILE);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&room", room);
    mx_replace_str(&tmp, "&user", user);
    mx_replace_str(&tmp, "&time", times);
    mx_strdel(&times);
    return tmp;
}
