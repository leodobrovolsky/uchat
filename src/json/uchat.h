#include "libmx.h"
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
#define CONNECT_REQUEST_FILE "mx_connect_request.json"
#define CONNECT_RESPONSE_FILE "mx_connect_response.json"
#define AUTORIZATION_REQUEST_FILE "mx_autorization_request.json"
#define AUTORIZATION_RESPONSE_FILE "mx_autorization_response.json"
#define REGISTER_REQUEST_FILE "mx_register_request.json"
#define REGISTER_RESPONSE_FILE "mx_register_response.json"
#define EDIT_USER_REQUEST_FILE "mx_edit_user_request.json"
#define EDIT_USER_RESPONSE_FILE "mx_edit_user_response.json"
#define GET_MESSAGES_REQUEST_FILE "mx_get_messages_request.json"
#define GET_MESSAGES_RESPONSE_FILE "mx_get_messages_response.json"
#define MESSAGE_FILE "mx_message.json"
#define GET_ROOMS_REQUEST_FILE "mx_get_rooms_request.json"
#define GET_ROOMS_RESPONSE_FILE "mx_get_rooms_response.json"
#define ROOMS_FILE "mx_rooms.json"
#define GET_USERS_IN_ROOMS_REQUEST_FILE "mx_get_users_in_rooms_request.json"
#define GET_USERS_IN_ROOMS_RESPONSE_FILE "mx_get_users_in_rooms_response.json"
#define LEAV_ROOM_REQUEST_FILE "mx_leav_room_request.json"
#define LEAV_ROOM_RESPONSE_FILE "mx_leav_room_response.json"
#define ADD_USER_TO_ROOM_REQUEST_FILE "mx_add_user_to_room_request.json"
#define ADD_USER_TO_ROOM_RESPONSE_FILE "mx_add_user_to_room_response.json"
#define LOAD_PROFILE_REQUEST_FILE "mx_load_profile_request.json"
#define LOAD_PROFILE_RESPONSE_FILE "mx_load_profile_response.json"
#define CREATE_ROOM_REQUEST_FILE "mx_create_room_request.json"
#define CREATE_ROOM_RESPONSE_FILE "mx_create_room_response.json"


//response status error

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


