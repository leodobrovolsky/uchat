#include "uchat.h"

static void mx_get_mes2(char **tmp_mes, t_list_arr *mes) {
    *tmp_mes = mx_file_to_str(MESSAGE_FILE);
    mx_replace_str(tmp_mes, "&time", mes->data[0]);
    mx_replace_str(tmp_mes, "&user", mes->data[1]);
    mx_replace_str(tmp_mes, "&text", mes->data[2]);
}

char *mx_get_messages_response_to_json(t_list_arr *mes, char *r, int status) {
    char *tmp = mx_file_to_str(GET_MESSAGES_RESPONSE_FILE);
    char *times = mx_get_current_time();
    char *st = mx_itoa(status);
    char *tmp_mes = NULL;

    mx_replace_str(&tmp, "&id", times);
    mx_replace_str(&tmp, "&status", st);
    mx_replace_str(&tmp, "&room", r);
    while(mes) {
        mx_get_mes2(&tmp_mes, mes);
        mx_stradd(&tmp, tmp_mes);
        if (mes->next)
            mx_stradd(&tmp, ",");
        mes = mes->next;
        mx_strdel(&tmp_mes);
    }
    mx_stradd(&tmp, "]}");
    mx_strdel(&times);
    mx_strdel(&st);
    return tmp;
}
