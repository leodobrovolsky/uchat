#include "uchat.h"

t_table *mx_create_t_table_messages() {
    t_table *messages = NULL;

    mx_push_t_table(&messages, "id", "PRIMARY KEY", "INTEGER");
    mx_push_t_table(&messages, "time", NULL, "INTEGER");
    mx_push_t_table(&messages, "user_id", NULL, "INTEGER");
    mx_push_t_table(&messages, "room_id", NULL, "INTEGER");
    mx_push_t_table(&messages, "text", NULL, "TEXT");
    return messages;
}
