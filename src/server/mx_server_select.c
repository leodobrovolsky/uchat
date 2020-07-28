#include "uchat.h"

void mx_server_select() {
    char *tmp = mx_strnew(SERVER_INPUT_SIZE);
    char *table = NULL;
    char *cond = NULL;
    t_list_arr *res = NULL;

    mx_printstr("Имя таблицы -> ");
    mx_getch(tmp);
    table = mx_strdup(tmp);
    mx_strdel(&tmp);
    mx_printstr("Условие -> ");
    tmp = mx_strnew(SERVER_INPUT_SIZE);
    mx_getch(tmp);
    cond = mx_strdup(tmp);
    mx_strdel(&tmp);
    res = mx_get_select(table, cond);
    mx_print_list_arr(res);
    mx_free_arr_list(&res);  
}
