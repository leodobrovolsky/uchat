#include "uchat.h"

t_table *mx_create_t_table_users_rooms() {
    t_table *users_rooms = NULL;

    mx_push_t_table(&users_rooms, "user_id", NULL, "INTEGER");
    mx_push_t_table(&users_rooms, "room_id", NULL, "INTEGER");
    return users_rooms;
}
