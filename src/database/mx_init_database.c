#include "uchat.h"

void mx_init_database() {
    t_table *users = mx_create_t_table_users();
    t_table *rooms = mx_create_t_table_rooms();
    t_table *users_rooms = mx_create_t_table_users_rooms();
    t_table *messages = mx_create_t_table_messages();
    t_table *active_users = mx_create_t_table_active_users();
    t_database db;

    mx_create_db(DATABASE_NAME);
    db.name_db = DATABASE_NAME;
    db.name_table = TABLE_NAME_USERS;

    //create table users
    db.table = users;
    mx_create_table(db);
    mx_free_t_table(&users);

    //create table rooms
    db.name_table = TABLE_NAME_ROOMS;
    db.table = rooms;
    mx_create_table(db);
    mx_free_t_table(&rooms);

    //create table users_rooms
    db.table = users_rooms;
    db.name_table = TABLE_NAME_USERS_ROOMS;
    mx_create_table(db);
    mx_free_t_table(&users_rooms);

    //create table messages
    db.table = messages;
    db.name_table = TABLE_NAME_MESSAGES;
    mx_create_table(db);
    mx_free_t_table(&messages);

    //create table active_users
    db.table = active_users;
    db.name_table = TABLE_NAME_ACTIVE_USERS;
    mx_create_table(db);
    mx_free_t_table(&active_users);
}
