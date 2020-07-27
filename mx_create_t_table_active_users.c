#include "uchat.h"

t_table *mx_create_t_table_active_users() {
    t_table *active_users = NULL;

    mx_push_t_table(&active_users, "id", "PRIMARY KEY", "INTEGER");
    mx_push_t_table(&active_users, "user_id", NULL, "INTEGER");
    mx_push_t_table(&active_users, "fd", NULL, "INTEGER");
    return active_users;
}
