#include "uchat.h"

void mx_pop_front_table(t_table **table) {
    t_table *tmp = *table;

    if (*table == NULL)
        return;
    if (tmp->next == NULL) {
        free(*table);
        *table = NULL;
        return;
    }
    *table = tmp->next;
    free(tmp);
    tmp = NULL;
}
