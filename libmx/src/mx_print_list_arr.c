#include "libmx.h"

void mx_print_list_arr(t_list_arr *list) {
    t_list_arr *tmp = list;

    while(tmp) {
        mx_print_strarr(tmp->data, " | ");
        tmp = tmp->next;
    }
}
