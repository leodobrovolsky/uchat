#include "uchat.h"

static char *mx_get_column_type(t_table *table, char *name) {
    t_table *tmp = table;

    while (tmp) {
        if (!mx_strcmp(tmp->name, name))
            return tmp->type;
        tmp = tmp->next;
    }
    return NULL;
}

static bool mx_c2(t_database t_db, char *unique1, char *unique2, int columns) {
    char *condition = NULL;
    t_list_arr *res = NULL;
    char *type = NULL;
    bool check = false;

    mx_stradd(&condition, "WHERE ");
    mx_stradd(&condition, unique1);
    mx_stradd(&condition, " = ");
    type = mx_get_column_type(t_db.table, unique1);
    if (!mx_strcmp(type, "TEXT"))
        mx_stradd(&condition, "'");
    mx_stradd(&condition, unique2);
    if (!mx_strcmp(type, "TEXT"))
        mx_stradd(&condition, "'");        
    res = mx_select_table(t_db, condition, columns);
    if (res) 
        check = true;
    mx_strdel(&condition);
    mx_free_arr_list(&res);
    return check;
}

bool mx_check_unique_update_data(t_database t_db, char **unique, int columns) {
    bool check = false;

    if (!unique)
        return false;
    for (int i = 0; unique[i]; i += 2) {
        check = mx_c2(t_db, unique[i], unique[i+1], columns);
        if (check)
            return true;
    }
    return false;
}