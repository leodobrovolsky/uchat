#include "libmx.h"

void mx_arr_push_front(t_list_arr **list, char **data) {
    t_list_arr *front = mx_create_list_arr(data);

    if (*list == NULL) {
        *list = front;
        return;
    }
    front -> next = *list;
    *list = front;
}
