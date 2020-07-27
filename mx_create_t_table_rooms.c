#include "uchat.h"

t_table *mx_create_t_table_rooms() {
    t_table *rooms = NULL;

    mx_push_t_table(&rooms, "id", "PRIMARY KEY", "INTEGER");
    mx_push_t_table(&rooms, "name", NULL, "TEXT");
    return rooms;   
}
