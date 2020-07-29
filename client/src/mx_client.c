#include <gtk/gtk.h>
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

#define SERVER_MAX_USERS 20

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
#define SERVER_INPUT_SIZE 30
#define SERVER_COM_HELP "/help"
#define SERVER_COM_CREATE_MANAGER "/create_manager"
#define SERVER_COM_DELETE_MANAGER "/delete_manager"
#define SERVER_COM_EDIT_MANAGER "/edit_manager"
#define SERVER_COM_MANAGERS "/managers"
#define SERVER_COM_EXIT "/exit"
#define SERVER_COM_ABORT "/abort"
#define SERVER_COM_SELECT "/select"
#define SERVER_HELP "/help - справка\n/exit - выход\n/create_manager - создать менеджера\n/delete_manager - удалить менеджера\n/edit_manager - изменить данные о менеджере\n/managers - вывести список менеджеров\n/select - показать выборку таблицы\n"


#define USER_TYPE_USUAL "usual"
#define USER_TYPE_MANAGER "manager"
#define USER_TYPE_ADMIN "admin"
#define USER_STATUS_ACTIVE "active"
#define USER_STATUS_BAN "ban"


#define SOCKET_BUFFER_SIZE 1025
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

//gtk
#define WINDOW_AUTHOR "Авторизация"

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

// typedef struct s_client {
//     t_user_create *user;
//     int sock_fd;
//     char *active_room;
//     t_list_arr *rooms;
//     t_list_arr *users;
//     t_list_arr *messages;
//     struct sockaddr_in svaddr;
//     char *buf;
//     t_form_auth *form_auth;
// } t_client;

typedef struct s_form_auth {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    GtkWidget *button_exit;
    GtkWidget *u_name;
    GtkWidget *pass;
    GtkWidget *label_user;
    GtkWidget *label_pass;
} t_form_auth;

typedef struct s_form_rooms {
    GtkWidget *window;
} t_form_rooms;

typedef struct s_form_users {
    GtkWidget *window;   
} t_form_users;

typedef struct s_form_messages {
    GtkWidget *window;
} t_form_messages;

typedef struct s_client {
    t_user_create *user;
    int sock_fd;
    char *active_room;
    t_list_arr *rooms;
    t_list_arr *users;
    t_list_arr *messages;
    struct sockaddr_in svaddr;
    char *buf;
    t_form_auth *form_auth;
} t_client;


void mx_client_config_socket(t_client **client, char *IP, char *port) {
    t_client *c = *client;
     struct hostent *serv = NULL;

    c->sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (c->sock_fd < 0)
        mx_print_error("Error create socket", 1, true);
    serv = gethostbyname(IP);    
    if(!serv) {
        write(2, "uchat error:: no host\n", 22);
        exit(1);
    }
    mx_memset(&c->svaddr, 0, sizeof(struct sockaddr_in));
    c->svaddr.sin_family = AF_INET;
    mx_strncpy((char*)&c->svaddr.sin_addr.s_addr,(char*)serv->h_addr,serv->h_length);
    c->svaddr.sin_port = htons(mx_atoi(port)); 
    if (inet_pton(AF_INET, IP, &c->svaddr.sin_addr) <= 0)
        mx_print_error("error inet_pton\n", 1, true);
    if (connect(c->sock_fd, (struct sockaddr *)&c->svaddr, sizeof(struct sockaddr_in)) != 0)
        mx_print_error("error connect\n", 1, true);
}

void mx_check_autorization(GtkWidget *widget, gpointer data) {
    t_client *c = *(t_client*)&data;

    mx_printstr(c->user)
}


bool mx_client_request_autorization(t_client *c) {
    //char *str = mx_autorization_request_to_json(c->user->login, c->user->passwd);

    //mx_client_send(str);
    //mx_strdel(&str);
    mx_printstr(c->user->login);
    return true;
}



void *mx_run_gtk(void *void_client) {
    t_client *c = (t_client*)void_client;
    int status = 0;

    gtk_init (NULL, NULL);

    /* create a new window, set its title and put it on center */
    c->form_auth->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (c->form_auth->window), WINDOW_AUTHOR);
    gtk_window_set_position(GTK_WINDOW(c->form_auth->window), GTK_WIN_POS_CENTER);
    g_signal_connect (c->form_auth->window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (c->form_auth->window), 10);
    gtk_window_set_resizable(GTK_WINDOW(c->form_auth->window), FALSE); /* window is NOT resizable */

    /* Here we construct the container that is going pack our buttons */
    c->form_auth->grid = gtk_grid_new();
    gtk_grid_set_row_spacing (GTK_GRID (c->form_auth->grid), 3);

    /* Pack the container in the window */
    gtk_container_add (GTK_CONTAINER (c->form_auth->window), c->form_auth->grid);

    /* Add labels */
    c->form_auth->label_user = gtk_label_new("Логин     ");
    //label_host = gtk_label_new("Hostname  ");
    c->form_auth->label_pass = gtk_label_new("Пароль  ");

    /* Add hostname entry and label */
    //h_name = gtk_entry_new();
    //gtk_entry_set_placeholder_text (GTK_ENTRY (h_name), "Hostname"); /* imposto il testo trasparente che scompare quando clicco o scrivo */
    //gtk_grid_attach (GTK_GRID (grid), label_host, 0, 0, 1, 1);
    //gtk_grid_attach (GTK_GRID (grid), h_name, 1, 0, 1, 1);

    /* Add username entry and label */
    c->form_auth->u_name = gtk_entry_new();
    gtk_entry_set_placeholder_text (GTK_ENTRY (c->form_auth->u_name), "Логин");
    gtk_grid_attach (GTK_GRID (c->form_auth->grid), c->form_auth->label_user, 0, 1, 1, 1);
    gtk_grid_attach (GTK_GRID (c->form_auth->grid), c->form_auth->u_name, 1, 1, 2, 1);

    /* Add password entry and label (visibility set to 0 = not visible */
    c->form_auth->pass = gtk_entry_new();
    gtk_entry_set_placeholder_text (GTK_ENTRY (c->form_auth->pass), "Пароль");
    gtk_grid_attach (GTK_GRID (c->form_auth->grid), c->form_auth->label_pass, 0, 2, 1, 1);
    gtk_entry_set_visibility (GTK_ENTRY (c->form_auth->pass), 0);
    gtk_grid_attach (GTK_GRID (c->form_auth->grid), c->form_auth->pass, 1, 2, 1, 1);

    /* Add connect button */
    c->form_auth->button = gtk_button_new_with_label ("Вход");
    g_signal_connect (c->form_auth->button, "clicked", G_CALLBACK (mx_check_autorization), c);  // your funct
    gtk_grid_attach (GTK_GRID (c->form_auth->grid), c->form_auth->button, 0, 3, 2, 1);

    /* Add quit button */
    c->form_auth->button_exit = gtk_button_new_with_label ("Выход");
    g_signal_connect (c->form_auth->button, "clicked", G_CALLBACK (gtk_main_quit), NULL);
    gtk_grid_attach (GTK_GRID (c->form_auth->grid), c->form_auth->button, 0, 4, 2, 1);

    /* Now that we are done packing our widgets, we show them all in one go, by calling gtk_widget_show_all() on the window.*/
    gtk_widget_show_all (c->form_auth->window);

    /* All GTK applications must have a gtk_main(). Control ends here and waits for an event to occur (like a key press or a mouse event),
     * until gtk_main_quit() is called. */
    gtk_main ();
    // gtk_init(NULL, NULL);
    // c->win = gtk_application_new(NULL, G_APPLICATION_FLAGS_NONE); 
    // g_signal_connect(c->win, "activate", G_CALLBACK(gtk_loop), c);
    // status = g_application_run(G_APPLICATION(c->win), 0, NULL);
    // g_object_unref(c->win);
    return NULL;
}


int main(int argc, char *argv[]) {
    t_client *client = malloc(sizeof(t_client));
    pthread_t recv_thread;

    if (argc != 3)
        mx_print_error("Usage ./uchat_client %IP adress %port\n", 1, true);
    //mx_client_config_socket(&client, argv[1], argv[2]);
    //connect to server
    // mx_client_create_request(client, 0);
    // usleep(100);
    // pthread_create(&recv_thread, NULL, mx_recv_loop, (void*)&client);
    // mx_client_create_request(client, 1);
    // mx_client_create_request(client, 0);
    mx_run_gtk((void*)&client);
    //pthread_join(recv_thread, NULL);
}
