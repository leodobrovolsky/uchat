#include "uchat.h"

t_table *mx_create_t_table_users() {
    t_table *users = NULL;

    mx_push_t_table(&users, "id", "PRIMARY KEY", "INTEGER");
    mx_push_t_table(&users, "login", NULL, "TEXT");
    mx_push_t_table(&users, "password", NULL, "TEXT");
    mx_push_t_table(&users, "name", NULL, "TEXT");
    mx_push_t_table(&users, "surname", NULL, "TEXT");
    mx_push_t_table(&users, "email", NULL, "TEXT");
    mx_push_t_table(&users, "rules", NULL, "TEXT");
    mx_push_t_table(&users, "status", NULL, "TEXT");
    return users; 
}
