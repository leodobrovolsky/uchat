#include "uchat.h"

char *mx_get_users_in_rooms_response_to_json(char *room, char **users, int status) {
    char *tmp = mx_file_to_str(GET_USERS_IN_ROOMS_RESPONSE_FILE);
    char *st = mx_itoa(status);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&time", times);
    mx_replace_str(&tmp, "&status", st);
    mx_replace_str(&tmp, "&room", room);
    for (int i = 0; users[i]; i++) {
        mx_stradd(&tmp, "\"");
        mx_stradd(&tmp, users[i]);
        mx_stradd(&tmp, "\"");
        if (users[i+1])
            mx_stradd(&tmp, ",");
    }
    mx_stradd(&tmp, "]}");
    mx_strdel(&times);
    mx_strdel(&st);
    return tmp;
}
