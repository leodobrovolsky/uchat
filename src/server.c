#include "uchat.h"


// void mx_config_server(t_server_main **s) {

// }


// int mx_getch(char *input_str) {
//     int size = 0;

//     size = read(0, input_str, SERVER_INPUT_SIZE);
//     input_str[size - 1] = '\0';
//     return size;
// }

// void mx_run_help() {
//     mx_printstr(SERVER_HELP);
// }

// t_table *mx_create_t_table_users() {
//     t_table *users = NULL;

//     mx_push_t_table(&users, "id", "PRIMARY KEY", "INTEGER");
//     mx_push_t_table(&users, "login", NULL, "TEXT");
//     mx_push_t_table(&users, "password", NULL, "TEXT");
//     mx_push_t_table(&users, "name", NULL, "TEXT");
//     mx_push_t_table(&users, "surname", NULL, "TEXT");
//     mx_push_t_table(&users, "email", NULL, "TEXT");
//     mx_push_t_table(&users, "rules", NULL, "TEXT");
//     mx_push_t_table(&users, "status", NULL, "TEXT");
//     return users; 
// }

// void mx_insert_user(t_user_create user) {
//     t_table *table = mx_create_t_table_users();
//     t_database db;
//     char **user_arr = mx_create_char_arr(TABLE_USERS_COLUMNS);

//     user_arr[0] = mx_strdup("NULL");
//     user_arr[1] = mx_strdup(user.login);
//     user_arr[2] = mx_strdup(user.password);
//     user_arr[3] = mx_strdup(user.name);
//     user_arr[4] = mx_strdup(user.surname);
//     user_arr[5] = mx_strdup(user.email);
//     user_arr[6] = mx_strdup(user.rules);
//     user_arr[7] = mx_strdup("active");

//     db.name_db = DATABASE_NAME;
//     db.name_table = TABLE_NAME_USERS;
//     mx_push_data_table(&table, user_arr);
//     db.table = table;
//     mx_insert_data(db);
//     mx_free_t_table(&db.table);
// }

// char *mx_valid_input_password() {
//     char *passwd1 = mx_strnew(SERVER_INPUT_SIZE);
//     char *passwd2 = mx_strnew(SERVER_INPUT_SIZE);
//     int res = 0;

//     mx_printstr("Введите пароль-> ");
//     mx_getch(passwd1);
//     mx_printstr("Введите пароль еще раз-> ");
//     mx_getch(passwd2); 
//     res = mx_strcmp(passwd1, passwd2);
//     mx_strdel(&passwd2);
//     if (!res)
//         return passwd1;
//     else {
//         mx_printstr("Пароли не совпадают! Попробуйте еще раз\n");
//         mx_strdel(&passwd1);
//         return NULL;
//     }
// }

// void mx_server_create_manager() {
//     t_user_create user;
//     char *check = mx_strnew(SERVER_INPUT_SIZE);

//     mx_printstr("Введите логин-> ");
//     user.login = mx_strnew(SERVER_INPUT_SIZE);
//     mx_getch(user.login);
//     user.password = mx_valid_input_password();
//     if (!user.password)
//         return;
//     mx_printstr("Введите имя-> ");
//     user.name = mx_strnew(SERVER_INPUT_SIZE);
//     mx_getch(user.name);
//     mx_printstr("Введите фамилию-> ");
//     user.surname = mx_strnew(SERVER_INPUT_SIZE);
//     mx_getch(user.surname);
//     mx_printstr("Введите email-> ");
//     user.email = mx_strnew(SERVER_INPUT_SIZE);
//     mx_getch(user.email);
//     user.rules = mx_strdup("manager");
//     mx_printstr("Логин: ");
//     mx_printstr(user.login);
//     mx_printstr("\nПароль: ");
//     mx_printstr(user.password);
//     mx_printstr("\nИмя: ");
//     mx_printstr(user.name);
//     mx_printstr("\nФамилия: ");
//     mx_printstr(user.surname);
//     mx_printstr("\nEmail: ");
//     mx_printstr(user.email);
//     mx_printstr("\nСохранить y/n ? ");
//     mx_getch(check);
//     if (!mx_strcmp(check, "y")) {
//         mx_insert_user(user);
//         mx_printstr("Менеджер добавлен!\n");
//     }
//     else
//         mx_printstr("Отмена добавления\n");
// }

// void mx_server_managers() {
//     t_table *table = NULL;
//     t_list_arr *arr = NULL;
//     t_database db;
//     char *condition = NULL;

//     db.name_db = DATABASE_NAME;
//     db.name_table = TABLE_NAME_USERS;
//     table = mx_create_t_table_users();
//     db.table = table;
//     arr = mx_select_table(db, "WHERE rules = 'manager'", 5);
//     mx_print_list_arr(arr);
//     mx_free_arr_list(&arr);
//     mx_free_t_table(&table);
//     mx_strdel(&condition);
// }

// void mx_server_delete_manager() {
//     char *manager = mx_strnew(SERVER_INPUT_SIZE);
//     t_list_arr *res = NULL;
//     t_database db;
//     t_table *table = NULL;
//     char *condition = NULL;
//     char *check = mx_strnew(SERVER_INPUT_SIZE);

//     mx_printstr("Введите логин менеджера-> ");
//     mx_getch(manager);
//     db.name_db = DATABASE_NAME;
//     db.name_table = "users";
//     mx_push_t_table(&table, "login", NULL, "TEXT");
//     db.table = table;
//     condition = mx_strjoin("WHERE login ='", manager);
//     mx_stradd(&condition, "';");
//     res = mx_select_table(db, condition, 1);
//     if (res) {
//         mx_printstr("Удалить менеджера ");
//         mx_printstr(manager);
//         mx_printstr(" y/n ? ");
//         mx_getch(check);
//         if (!mx_strcmp(check, "y")) {
//             mx_delete_data(db, condition);
//             mx_printstr("Менеджер удален!\n");
//         }
//     }
//     else
//         mx_printstr("Менеджер не найден!\n");
//     mx_free_t_table(&db.table);
//     mx_strdel(&condition);
//     mx_strdel(&check);
// }

// //void mx_update_user()


// void mx_server_edit_manager() {
//     char *manager = mx_strnew(SERVER_INPUT_SIZE);
//     t_database db;
//     bool check_unique = false;

//     mx_printstr("Введите логин менеджера-> ");
//     mx_getch(manager);

// }

// void mx_parse_com(char *str) {

//     if (!mx_strcmp(str, SERVER_COM_HELP))
//         mx_run_help();
//     else if (!mx_strcmp(str, SERVER_COM_CREATE_MANAGER))
//         mx_server_create_manager();
//     else if (!mx_strcmp(str, SERVER_COM_MANAGERS))
//         mx_server_managers();
//     else if (!mx_strcmp(str, SERVER_COM_EXIT))
//         exit(0);
//     else if (!mx_strcmp(str, SERVER_COM_DELETE_MANAGER))
//         mx_server_delete_manager();
//     else if (!mx_strcmp(str, SERVER_COM_EDIT_MANAGER))
//         mx_server_edit_manager();
// }

// void mx_server_begin(t_server_main *s) {
//     int size = 0;

//     mx_print_str("Введите /help для справки\n");
//     while(1) {
//         mx_printstr("server-> ");
//         s->input_str = mx_strnew(SERVER_INPUT_SIZE);
//         size = mx_getch(s->input_str);
//         if (size <= 0) {
//             mx_strdel(&s->input_str);
//             continue;
//         }
//         //mx_printstr(s->input_str);
//         mx_parse_com(s->input_str);
//         mx_strdel(&s->input_str);
//     }
// }

// t_table *mx_create_t_table_rooms() {
//     t_table *rooms = NULL;

//     mx_push_t_table(&rooms, "id", "PRIMARY KEY", "INTEGER");
//     mx_push_t_table(&rooms, "name", NULL, "TEXT"); 
//     return rooms;   
// }

// t_table *mx_create_t_table_users_rooms() {
//     t_table *users_rooms = NULL;

//     mx_push_t_table(&users_rooms, "user_id", NULL, "INTEGER");
//     mx_push_t_table(&users_rooms, "room_id", NULL, "INTEGER");
//     return users_rooms;
// }

// t_table *mx_create_t_table_messages() {
//     t_table *messages = NULL;

//     mx_push_t_table(&messages, "id", "PRIMARY KEY", "INTEGER");
//     mx_push_t_table(&messages, "time", NULL, "INTEGER");
//     mx_push_t_table(&messages, "user_id", NULL, "INTEGER");
//     mx_push_t_table(&messages, "room_id", NULL, "INTEGER");
//     mx_push_t_table(&messages, "text", NULL, "TEXT");
//     return messages;
// }

// t_table *mx_create_t_table_active_users() {
//     t_table *active_users = NULL;

//     mx_push_t_table(&active_users, "id", "PRIMARY KEY", "INTEGER");
//     mx_push_t_table(&active_users, "user_id", NULL, "INTEGER");
//     mx_push_t_table(&active_users, "fd", NULL, "INTEGER");
//     return active_users;
// }

// void mx_init_database() {
//     t_table *users = mx_create_t_table_users();
//     t_table *rooms = mx_create_t_table_rooms();
//     t_table *users_rooms = mx_create_t_table_users_rooms();
//     t_table *messages = mx_create_t_table_messages();
//     t_table *active_users = mx_create_t_table_active_users();
//     t_database db;

//     mx_create_db(DATABASE_NAME);
//     db.name_db = DATABASE_NAME;
//     db.name_table = TABLE_NAME_USERS;

//     //create table users
//     db.table = users;
//     mx_create_table(db);
//     mx_free_t_table(&users);

//     //create table rooms
//     db.name_table = TABLE_NAME_ROOMS;
//     db.table = rooms;
//     mx_create_table(db);
//     mx_free_t_table(&rooms);

//     //create table users_rooms
//     db.table = users_rooms;
//     db.name_table = TABLE_NAME_USERS_ROOMS;
//     mx_create_table(db);
//     mx_free_t_table(&users_rooms);

//     //create table messages
//     db.table = messages;
//     db.name_table = TABLE_NAME_MESSAGES;
//     mx_create_table(db);
//     mx_free_t_table(&messages);

//     //create table active_users
//     db.table = active_users;
//     db.name_table = TABLE_NAME_ACTIVE_USERS;
//     mx_create_table(db);
//     mx_free_t_table(&active_users);       
// }

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


