#include "libmx.h"
#include "sqlite3.h"
#include "cJSON.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <gtk/gtk.h>

//logs
#define PRINT_JSON_ERROR 1
#define EXIT_PRINT_ERROR 1

//cJSON
#define JSON_TYPE_REQUEST "request"
#define JSON_TYPE_RESPONSE "response"

//database define
#define DATABASE_NAME "database.db"
#define TABLE_NAME_USERS "users"
#define TABLE_NAME_ROOMS "rooms"
#define TABLE_NAME_USERS_ROOMS "users_rooms"
#define TABLE_NAME_MESSAGES "messages"
#define TABLE_NAME_ACTIVE_USERS "active_users"
#define TABLE_USERS_COLUMNS 8
#define TABLE_ROOMS_COLUMNS 2
#define TABLE_USERS_ROOMS_COLUMNS 2
#define TABLE_MESSAGES_COLUMNS 5
#define TABLE_ACTIVE_USERS_COLUMNS 3
#define BUFFER_SIZE 1025
#define WINDOW_MAIN_WEIGHT 1000
#define WINDOW_MAIN_HEIGHT 700
#define SERVER_INPUT_SIZE 20
#define SERVER_COM_HELP "/help"
#define SERVER_COM_CREATE_MANAGER "/create_manager"
#define SERVER_COM_DELETE_MANAGER "/delete_manager"
#define SERVER_COM_EDIT_MANAGER "/edit_manager"
#define SERVER_COM_MANAGERS "/managers"
#define SERVER_COM_EXIT "/exit"
#define SERVER_COM_ABORT "/abort"
#define SERVER_HELP "/help - справка\n/exit - выход\n/create_manager - создать менеджера\n/delete_manager - удалить менеджера\n/edit_manager - изменить данные о менеджере\n/managers - вывести список менеджеров\n"


#define USER_TYPE_USUAL "usual"
#define USER_TYPE_MANAGER "manager"
#define USER_TYPE_ADMIN "admin"
#define USER_STATUS_ACTIVE "active"
#define USER_STATUS_BAN "ban"


#define BUFFER_SIZE 1025
#define WINDOW_MAIN_WEIGHT 1000
#define WINDOW_MAIN_HEIGHT 700

//type of request
#define REQ_CONNECT 0
#define REQ_AUTORIZATION 1
#define REQ_REGISTER 2
#define REQ_EDIT_USER 3
#define REQ_GET_MESSAGES 4
#define REQ_GET_ROOMS 5
#define REQ_GET_USERS_IN_ROOMS 6
#define REQ_LEAV_ROOM 7
#define REQ_ADD_USER_TO_ROOM 8
#define REQ_LOAD_PROFILE 9
#define REQ_CREATE_ROOM 10


//filename json
#define CONNECT_REQUEST_FILE "src/json_files/mx_connect_request.json"
#define CONNECT_RESPONSE_FILE "src/json_files/mx_connect_response.json"
#define AUTORIZATION_REQUEST_FILE "src/json_files/mx_autorization_request.json"
#define AUTORIZATION_RESPONSE_FILE "src/json_files/mx_autorization_response.json"
#define REGISTER_REQUEST_FILE "src/json_files/mx_register_request.json"
#define REGISTER_RESPONSE_FILE "src/json_files/mx_register_response.json"
#define EDIT_USER_REQUEST_FILE "src/json_files/mx_edit_user_request.json"
#define EDIT_USER_RESPONSE_FILE "src/json_files/mx_edit_user_response.json"
#define GET_MESSAGES_REQUEST_FILE "src/json_files/mx_get_messages_request.json"
#define GET_MESSAGES_RESPONSE_FILE "src/json_files/mx_get_messages_response.json"
#define MESSAGE_FILE "src/json_files/mx_message.json"
#define GET_ROOMS_REQUEST_FILE "src/json_files/mx_get_rooms_request.json"
#define GET_ROOMS_RESPONSE_FILE "src/json_files/mx_get_rooms_response.json"
#define ROOMS_FILE "src/json_files/mx_rooms.json"
#define GET_USERS_IN_ROOMS_REQUEST_FILE "src/json_files/mx_get_users_in_rooms_request.json"
#define GET_USERS_IN_ROOMS_RESPONSE_FILE "src/json_files/mx_get_users_in_rooms_response.json"
#define LEAV_ROOM_REQUEST_FILE "src/json_files/mx_leav_room_request.json"
#define LEAV_ROOM_RESPONSE_FILE "src/json_files/mx_leav_room_response.json"
#define ADD_USER_TO_ROOM_REQUEST_FILE "src/json_files/mx_add_user_to_room_request.json"
#define ADD_USER_TO_ROOM_RESPONSE_FILE "src/json_files/mx_add_user_to_room_response.json"
#define LOAD_PROFILE_REQUEST_FILE "src/json_files/mx_load_profile_request.json"
#define LOAD_PROFILE_RESPONSE_FILE "src/json_files/mx_load_profile_response.json"
#define CREATE_ROOM_REQUEST_FILE "src/json_files/mx_create_room_request.json"
#define CREATE_ROOM_RESPONSE_FILE "src/json_files/mx_create_room_response.json"


//client
#define BUFFER_SIZE 1025
#define WINDOW_MAIN_WEIGHT 1000
#define WINDOW_MAIN_HEIGHT 700

// typedef struct s_client_main {
//     char *login;
//     char *name;
//     char *surname;
//     char **rooms;
//     GtkApplication *win;
//     GtkWidget *but;
// } t_client_main;

typedef struct s_user_create {
    char *id;
    char *login;
    char *password;
    char *name;
    char *surname;
    char *email;
    char *rules;
    char *status;
} t_user_create;

//server
typedef struct s_server {
    struct sockaddr_in svaddr;
    int sock_fd;
    int client_fd;
    char *input_str;
    bool exit_status;
    t_user_create *user;
} t_server;

//database
typedef struct s_table {
    char *name;
    char *params;
    char *type;
    char *data;
    struct s_table *next;
} t_table;

typedef struct s_database {
    char *name_db;
    char *name_table;
    t_table *table;
} t_database;

typedef struct s_client {
    int sock_fd;
    char *login;
    char *name;
    char *surname;
    char **rooms;
    GtkApplication *win;
    GtkWidget *but;
} t_client;

typedef struct s_message_create {
    char *room;
    char *user;
    char *time;
    char *text;
}t_message_create;

//database
void mx_create_db(char const *name_db);
void mx_create_table(const t_database t_db);
t_table *mx_create_t_table(char *name, char *params, char *type);
void mx_push_t_table(t_table **table, char *name, char *params, char *type);
void mx_push_data_table(t_table **table, char **datas);
void mx_free_t_table(t_table **table);
void mx_insert_data(const t_database t_db);
t_list_arr *mx_select_table(const t_database t_db, char *cond, int columns);
void mx_update_data(t_database t_db, char *condition);
t_table *mx_copy_struct_t_table(t_table *table);
void mx_delete_data(t_database t_db, char *condition);
bool mx_check_unique_update_data(t_database t_db, char **unique, int columns);
t_table *mx_create_t_table_users();
bool mx_insert_user(t_user_create *user);
t_table *mx_create_t_table_rooms();
t_table *mx_create_t_table_users_rooms();
t_table *mx_create_t_table_messages();
t_table *mx_create_t_table_active_users();
void mx_init_database();
bool mx_update_user(t_user_create *user, char *old_login);
void mx_pop_front_table(t_table **table);
char *mx_get_room_id(char *name);
char *mx_get_user_id(char *name);
t_list_arr *mx_server_get_mes_list(char *name);


//requst/responses to json 
char *mx_connect_request_to_json();
char *mx_connect_response_to_json(int status);
char *mx_autorization_request_to_json(char *login, char *passwd);
char *mx_autorization_response_to_json(int status);
char *mx_register_request_to_json(t_user_create *user);
char *mx_register_response_to_json(int status);
char *mx_edit_user_request_to_json(t_user_create *user, char *old_login);
char *mx_edit_user_response_to_json(int status);
char *mx_get_messages_request_to_json(char *room);
char *mx_get_messages_response_to_json(t_list_arr *mes, char *r, int status);
char *mx_get_rooms_request_to_json(char *user);
char *mx_get_rooms_response_to_json(char **rooms, int status);
char *mx_get_users_in_rooms_request_to_json(char *room, char *user);
char *mx_get_users_in_rooms_response_to_json(char *room, char **users, int status);
char *mx_leav_room_request_to_json(char *room, char *user);
char *mx_leav_room_response_to_json(int status);
char *mx_add_user_to_room_request_to_json(char *user, char *room);
char *mx_add_user_to_room_response_to_json(int status);
char *mx_load_profile_request_to_json(char *user);
char *mx_load_profile_response_to_json(t_user_create user, int status);
char *mx_create_room_request_to_json(char *name);
char *mx_create_room_response_to_json(int status);


//server
int mx_getch(char *input_str);
void mx_run_help();
char *mx_valid_input_password();
void mx_server_create_manager();
void mx_server_managers();
void mx_server_delete_manager();
void mx_server_edit_manager();
void mx_parse_com(char *str);
void mx_server_begin(t_server *s);
void mx_print_user_create(t_user_create *user);
char *mx_get_current_time();
void mx_free_user_create(t_user_create **user);

//parsing
t_user_create *mx_arr_to_user_create(char **arr);
char **mx_user_create_to_arr(t_user_create *user);
void mx_parse_json(t_server *main, char *str);
void mx_parse_request(t_server *main, cJSON *root, int time_int);
void mx_parse_response(t_server *main, cJSON *root, int time_int);
void mx_server_req_autorization(t_server *server, cJSON *root);
t_list_arr *mx_server_search_user(char *login, char *password);
void mx_server_req_connect(t_server *main);
void mx_print_error_json(cJSON *root);
void mx_server_req_get_messages(t_server *server, cJSON *root);

