#include "uchat.h"

char *mx_add_user_to_room_request_to_json(char *user, char *room) {
    char *tmp = mx_file_to_str(ADD_USER_TO_ROOM_REQUEST_FILE);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&room", room);
    mx_replace_str(&tmp, "&user", user);
    mx_replace_str(&tmp, "&time", times);
    mx_strdel(&times);
    return tmp;   
}
