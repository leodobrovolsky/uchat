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
#define TABLE_ACTIVE_USERS 3
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
#define SERVER_HELP "/help - справка\n/exit - выход\n/unset - отмена операции\n/create_manager - создать менеджера\n/delete_manager - удалить менеджера\n/edit_manager - изменить данные о менеджере\n/managers - вывести список менеджеров\n"
#define USER_TYPE_USUAL "usual"
#define USER_TYPE_MANAGER "manager"
#define USER_TYPE_ADMIN "admin"

#define BUFFER_SIZE 1025
#define WINDOW_MAIN_WEIGHT 1000
#define WINDOW_MAIN_HEIGHT 700

//type of request
#define REQ_CONNECT "0"
#define REQ_AUTORIZATION "1"
#define REQ_REGISTER "2"
#define REQ_EDIT_USER "3"
#define REQ_GET_MESSAGES "4"
#define REQ_GET_ROOMS "5"
#define REQ_GET_USERS_IN_ROOMS "6"
#define REQ_LEAV_ROOM "7"
#define REQ_ADD_USER_TO_ROOM "8"
#define REQ_LOAD_PROFILE "9"
#define REQ_CREATE_ROOM "10"


//filename json
#define CONNECT_REQUEST_FILE "json_files/mx_connect_request.json"
#define CONNECT_RESPONSE_FILE "json_files/mx_connect_response.json"
#define AUTORIZATION_REQUEST_FILE "json_files/mx_autorization_request.json"
#define AUTORIZATION_RESPONSE_FILE "json_files/mx_autorization_response.json"
#define REGISTER_REQUEST_FILE "json_files/mx_register_request.json"
#define REGISTER_RESPONSE_FILE "json_files/mx_register_response.json"
#define EDIT_USER_REQUEST_FILE "json_files/mx_edit_user_request.json"
#define EDIT_USER_RESPONSE_FILE "json_files/mx_edit_user_response.json"
#define GET_MESSAGES_REQUEST_FILE "json_files/mx_get_messages_request.json"
#define GET_MESSAGES_RESPONSE_FILE "json_files/mx_get_messages_response.json"
#define MESSAGE_FILE "json_files/mx_message.json"
#define GET_ROOMS_REQUEST_FILE "json_files/mx_get_rooms_request.json"
#define GET_ROOMS_RESPONSE_FILE "json_files/mx_get_rooms_response.json"
#define ROOMS_FILE "json_files/mx_rooms.json"
#define GET_USERS_IN_ROOMS_REQUEST_FILE "json_files/mx_get_users_in_rooms_request.json"
#define GET_USERS_IN_ROOMS_RESPONSE_FILE "json_files/mx_get_users_in_rooms_response.json"
#define LEAV_ROOM_REQUEST_FILE "json_files/mx_leav_room_request.json"
#define LEAV_ROOM_RESPONSE_FILE "json_files/mx_leav_room_response.json"
#define ADD_USER_TO_ROOM_REQUEST_FILE "json_files/mx_add_user_to_room_request.json"
#define ADD_USER_TO_ROOM_RESPONSE_FILE "json_files/mx_add_user_to_room_response.json"
#define LOAD_PROFILE_REQUEST_FILE "json_files/mx_load_profile_request.json"
#define LOAD_PROFILE_RESPONSE_FILE "json_files/mx_load_profile_response.json"
#define CREATE_ROOM_REQUEST_FILE "json_files/mx_create_room_request.json"
#define CREATE_ROOM_RESPONSE_FILE "json_files/mx_create_room_response.json"


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

typedef struct s_client_main {
    char *login;
    char *name;
    char *surname;
    char **rooms;
} t_client_main;

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

//requst/responses to json 
char *mx_connect_request_to_json();
char *mx_connect_response_to_json(int status);
char *mx_autorization_request_to_json(char *login, char *passwd);
char *mx_autorization_response_to_json(int status);
char *mx_register_request_to_json(t_user_create user);
char *mx_register_response_to_json(int status);
char *mx_edit_user_request_to_json(t_user_create user);
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