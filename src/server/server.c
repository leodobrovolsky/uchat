#include "uchat.h"

// void mx_config_server(t_server_main **s) {

// }

void mx_print_str(const char *s) {
    if (!s)
        write(1, "NULL\n", 5);
    else
        write(1, s, mx_strlen(s));
}

int mx_getch(char *input_str) {
    int size = 0;

    size = read(0, input_str, SERVER_INPUT_SIZE);
    input_str[size - 1] = '\0';
    return size;
}

void mx_run_help() {
    mx_printstr(SERVER_HELP);
}

t_table *mx_create_t_table_users() {
    t_table *users = NULL;

    mx_push_t_table(&users, "id", "PRIMARY KEY", "INTEGER");
    mx_push_t_table(&users, "login", NULL, "TEXT");
    mx_push_t_table(&users, "password", NULL, "TEXT");
    mx_push_t_table(&users, "name", NULL, "TEXT");
    mx_push_t_table(&users, "surname", NULL, "TEXT");
    mx_push_t_table(&users, "email", NULL, "TEXT");
    mx_push_t_table(&users, "rules", NULL, "TEXT");
    return users; 
}

void mx_insert_user(t_user_create user) {
    t_table *table = mx_create_t_table_users();
    t_database db;
    char **user_arr = mx_create_char_arr(TABLE_USERS_COLUMNS);

    user_arr[0] = mx_strdup("NULL");
    user_arr[1] = mx_strdup(user.login);
    user_arr[2] = mx_strdup(user.password);
    user_arr[3] = mx_strdup(user.name);
    user_arr[4] = mx_strdup(user.surname);
    user_arr[5] = mx_strdup(user.email);
    user_arr[6] = mx_strdup(user.rules);

    db.name_db = DATABASE_NAME;
    db.name_table = TABLE_NAME_USERS;
    mx_push_data_table(&table, user_arr);
    db.table = table;
    mx_insert_data(db);
}

void mx_server_create_manager() {
    t_user_create user;
    int size = 0;

    mx_printstr("Введите логин-> ");
    user.login = mx_strnew(SERVER_INPUT_SIZE);
    size = mx_getch(user.login);
    mx_printstr("Введите пароль-> ");
    user.password = mx_strnew(SERVER_INPUT_SIZE);
    mx_getch(user.password);
    mx_printstr("Введите имя-> ");
    user.name = mx_strnew(SERVER_INPUT_SIZE);
    mx_getch(user.name);
    mx_printstr("Введите фамилию-> ");
    user.surname = mx_strnew(SERVER_INPUT_SIZE);
    mx_getch(user.surname);
    mx_printstr("Введите email-> ");
    user.email = mx_strnew(SERVER_INPUT_SIZE);
    mx_getch(user.email);
    user.rules = mx_strdup("manager");
    mx_insert_user(user);
}

void mx_server_managers() {
    t_table *table = NULL;
    t_list_arr *arr = NULL;
    t_database db;

    db.name_db = DATABASE_NAME;
    db.name_table = TABLE_NAME_USERS;
    mx_push_t_table(&table, "id", "PRIMARY KEY", "INTEGER");
    mx_push_t_table(&table, "login", NULL, "TEXT");
    mx_push_t_table(&table, "name", NULL, "TEXT");
    mx_push_t_table(&table, "surname", NULL, "TEXT");
    mx_push_t_table(&table, "email", NULL, "TEXT");
    db.table = table;
    arr = mx_select_table(db, NULL, 4);
    mx_print_list_arr(arr);
    mx_free_arr_list(&arr);
    mx_free_t_table(&table);
}

void mx_parse_com(char *str) {

    if (!mx_strcmp(str, SERVER_COM_HELP))
        mx_run_help();
    if (!mx_strcmp(str, SERVER_COM_CREATE_MANAGER))
        mx_server_create_manager();
    if (!mx_strcmp(str, SERVER_COM_MANAGER))
        mx_server_managers();
}

void mx_server_begin(t_server_main *s) {
    int size = 0;

    mx_print_str("Введите /help для справки\n");
    while(1) {
        mx_printstr("server-> ");
        s->input_str = mx_strnew(SERVER_INPUT_SIZE);
        size = mx_getch(s->input_str);
        if (size <= 0) {
            mx_strdel(&s->input_str);
            continue;
        }
        //mx_printstr(s->input_str);
        mx_parse_com(s->input_str);
        mx_strdel(&s->input_str);
    }
}

void mx_init_database() {
    t_table *users = mx_create_t_table_users();
    t_table *rooms = NULL;
    t_table *users_rooms = NULL;
    t_table *messages = NULL;
    t_table *active_users = NULL;
    t_database db;

    mx_create_db(DATABASE_NAME);
    db.name_db = DATABASE_NAME;
    db.name_table = TABLE_NAME_USERS;

    //create table users
    db.table = users;
    mx_create_table(db);
    mx_free_t_table(&users);

    //create table rooms
    mx_push_t_table(&rooms, "id", "PRIMARY KEY", "INTEGER");
    mx_push_t_table(&rooms, "name", NULL, "TEXT");
    db.name_table = "rooms";
    db.table = rooms;
    mx_create_table(db);
    mx_free_t_table(&rooms);

    //create table users_rooms
    mx_push_t_table(&users_rooms, "user_id", NULL, "INTEGER");
    mx_push_t_table(&users_rooms, "room_id", NULL, "INTEGER");
    db.table = users_rooms;
    db.name_table = "users_rooms";
    mx_create_table(db);
    mx_free_t_table(&users_rooms);

    //create table messages
    mx_push_t_table(&messages, "id", "PRIMARY KEY", "INTEGER");
    mx_push_t_table(&messages, "time", NULL, "INTEGER");
    mx_push_t_table(&messages, "user_id", NULL, "INTEGER");
    mx_push_t_table(&messages, "room_id", NULL, "INTEGER");
    mx_push_t_table(&messages, "text", NULL, "TEXT");
    db.table = messages;
    db.name_table = "messages";
    mx_create_table(db);
    mx_free_t_table(&messages);

    //create table active_users
    mx_push_t_table(&active_users, "id", "PRIMARY KEY", "INTEGER");
    mx_push_t_table(&active_users, "user_id", NULL, "INTEGER");
    mx_push_t_table(&active_users, "fd", NULL, "INTEGER");
    db.table = active_users;
    db.name_table = "active_users";
    mx_create_table(db);
    mx_free_t_table(&active_users);       
}

int main(int argc, char *argv[]) {
    t_server_main *server = NULL;
    int fd = 0;

    if (argc != 2)
        mx_print_error("Usage ./uchat_server %PORT", 1, true);
    server = malloc(sizeof(t_server_main));
    fd = open(DATABASE_NAME, O_RDONLY);
    if (fd == -1)
        mx_init_database();
    mx_server_begin(server);
}
