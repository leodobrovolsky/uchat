#include "uchat.h"

char *mx_get_rooms_response_to_json(char **rooms, int status) {
    char *tmp = mx_file_to_str(GET_ROOMS_RESPONSE_FILE);
    char *st = mx_itoa(status);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&id", times);
    mx_replace_str(&tmp, "&status", st);
    for (int i = 0; rooms[i]; i++) {
        mx_stradd(&tmp, "\"");
        mx_stradd(&tmp, rooms[i]);
        mx_stradd(&tmp, "\"");
        if (rooms[i+1])
            mx_stradd(&tmp, ", ");
    }
    mx_stradd(&tmp, "]}");
    mx_strdel(&times);
    mx_strdel(&st);
    return tmp;
}
