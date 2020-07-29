#include "uchat.h"

#define CLIENT_AUTORIZATION "/autorization"
#define CLIENT_REGISTER "/register"
#define CLIENT_EDIT_USER "/edit_user"
#define CLIENT_MESSAGES_GET "/get_messages"
#define CLIENT_GET_ROOMS "/get_rooms"
#define CLIENT_USERS_IN_ROOM "/get_users_in_rooms"
#define CLIENT_LEAV_GROUP "/leav_group"
#define CLIENT_ADD_USER_TO_ROOM "/add_user_to_room"
#define CLIENT_LOAD_PROFILE "/load_profile"
#define CLIENT_CREATE_ROOM "/create_room"


// void mx_open_dialog(GtkWidget *button, void *void_client) {
//     t_client *c = (t_client*)void_client;
    
//     gtk_widget_show_all(c->but);
// }


// void gtk_loop(GtkWidget *window, void *void_client) {
//     t_client *c = (t_client*)void_client;
//     GtkWidget *button = NULL;
//     GtkWidget *main = NULL;


//     main = gtk_application_window_new(c->win);
//     gtk_window_new(GTK_WINDOW_TOPLEVEL);
//     gtk_window_set_position(GTK_WINDOW(main), GTK_WIN_POS_CENTER);
//     gtk_window_set_title(GTK_WINDOW(main), "UCHAT");
//     gtk_window_set_default_size(GTK_WINDOW(main), WINDOW_MAIN_WEIGHT, WINDOW_MAIN_HEIGHT);
//     button = gtk_button_new_with_label("Open dialog");
//     g_signal_connect(c->but, "clicked", G_CALLBACK(mx_open_dialog), c);
//     gtk_widget_show_all(main);
// }


// void *mx_run_gtk(void *void_client) {
//     t_client *c = *(t_client**)void_client;
//     int status = 0;

//     gtk_init(NULL, NULL);
//     c->win = gtk_application_new(NULL, G_APPLICATION_FLAGS_NONE); 
//     g_signal_connect(c->win, "activate", G_CALLBACK(gtk_loop), c);
//     status = g_application_run(G_APPLICATION(c->win), 0, NULL);
//     g_object_unref(c->win);
//     return NULL;
// }

//исправить segmantation fault
t_user_create *mx_copy_user_create(t_user_create *user) {
    t_user_create *tmp = malloc(sizeof(t_user_create));
    
    if (!user)
        return NULL;
    if (user->login)
        tmp->login = mx_strdup(user->login);
    if (user->password)
        tmp->password = mx_strdup(user->password);
    if (user->name)
        tmp->name = mx_strdup(user->name);
    if (user->surname)
        tmp->surname = mx_strdup(user->surname);
    if (user->email)
        tmp->email = mx_strdup(user->email);
    if (user->rules)
        tmp->rules = mx_strdup(user->rules);
    if (user->status)
        tmp->status = mx_strdup(user->status);
    mx_printstr("sef");
    return tmp;
}


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


void mx_client_response_autorization(t_client *c ,int status) {
    if (status == RESPONSE_AUTORIZATION_FAIL)
        c->autorized = false;
    else {
        c->autorized = true;
        if (status == RESPONSE_AUTORIZATION_USUAL)
            c->user->rules = mx_strdup(USER_TYPE_USUAL);
        else
            c->user->rules = mx_strdup(USER_TYPE_MANAGER);
    }
}

void mx_client_response_register(t_client *c, int status) {
    if (status == RESPONSE_REGISTER_OK)
        c->autorized = true;
    else
        c->autorized = false;
}

void mx_client_response_edit_user(t_client *c, int status) {
    if (status != RESPONSE_EDIT_USER_OK) {
        c->user = mx_copy_user_create(c->user_copy);
    }
}

void mx_client_parse_response(t_client *c, cJSON *root, int time_int) {
    int status = 0;
    int oper = 0;

    if (!root || !root->next)
        mx_print_error_json(root);
    status = root->valueint;
    oper = root->next->valueint;
    if (oper == REQ_AUTORIZATION)
        mx_client_response_autorization(c, status);
    else if (oper == REQ_REGISTER) 
        mx_client_response_register(c, status);
    else if (oper == REQ_EDIT_USER)
        mx_client_response_edit_user(c, status);
}


void mx_client_parse_json(t_client *main) {
    cJSON *root = cJSON_Parse(main->buf);
    int time_int = 0;
    mx_printstr(main->buf);
    if (!root || !(root->child)) 
        mx_print_error_json(root);
    root = root->child;
    time_int = root->valueint;
    if (!root->next)
        mx_print_error_json(root);
    root = root->next;
    if (!mx_strcmp(root->valuestring, JSON_TYPE_RESPONSE))
        mx_client_parse_response(main, root->next, time_int);
    else
        mx_print_error_json(root);
    cJSON_Delete(root);
    //здесь проверять структуру на изменения
}




// void *mx_recv_loop(void *client) {
//     t_client *c = *(t_client **)client;
//     int size = 0;

//     while(1) {
//         c->buf = mx_strnew(SOCKET_BUFFER_SIZE);
//         size = read(c->sock_fd, c->buf, SOCKET_BUFFER_SIZE);
//         mx_printint(size);
//         if (size > 0)
//             mx_client_parse_json(c);
//         mx_strdel(&c->buf);
//     }
// }

void mx_client_send(int fd, char *str) {
    write(fd, str, BUFFER_SIZE);
}

char *mx_client_recv(int fd) {
    int size = 0;
    char *buf = mx_strnew(SOCKET_BUFFER_SIZE);

    size = read(fd, buf, SOCKET_BUFFER_SIZE);
    if (size > 0)
        return buf;
    else
        return NULL;
}

void mx_client_request_get_messages(t_client *c) {
    char *str = mx_get_messages_request_to_json(c->active_room);

    mx_client_send(c->sock_fd, str);
    mx_strdel(&str);
}

void mx_client_request_edit(t_client *c) {
    char *str = mx_edit_user_request_to_json(c->user, c->current_login);

    mx_client_send(c->sock_fd, str);
    mx_strdel(&str);
}

void mx_client_request_register(t_client *c) {
    char *str = mx_register_request_to_json(c->user);
    
    mx_client_send(c->sock_fd, str);
    c->buf = mx_client_recv(c->sock_fd);
    mx_client_parse_json(c);
    mx_strdel(&str);
}

void mx_client_create_req_connect(t_client *c) {
    char *str = mx_connect_request_to_json();

    mx_client_send(c->sock_fd, str);
    mx_strdel(&str);
}

void mx_client_request_autorization(t_client *c) {
    char *str = mx_autorization_request_to_json(c->user->login, c->user->password);
    
    mx_client_send(c->sock_fd, str);
    c->buf = mx_client_recv(c->sock_fd);
    mx_client_parse_json(c);
    mx_strdel(&str);
}

void mx_client_create_request(t_client *client, int operation) {
    if (operation == REQ_CONNECT)
        mx_client_create_req_connect(client);
    else if (operation == REQ_REGISTER)
        mx_client_request_register(client);
    else if (operation == REQ_EDIT_USER)
        mx_client_request_edit(client);
    // else if (operation == REQ_GET_MESSAGES)
    //     mx_client_request_get_messages(client);
    else if (operation == REQ_AUTORIZATION)
        mx_client_request_autorization(client);
    // else if (operation == REQ_GET_ROOMS)
    //     mx_client_request_get_rooms(client);
    // else if (operation == REQ_GET_USERS_IN_ROOMS)
    //     mx_client_request_get_users_in_room(client);
}

void mx_client_autorization(t_client *c) {
    char *tmp = mx_strnew(SERVER_INPUT_SIZE);

    mx_printstr("Input login-> ");
    mx_getch(tmp);
    c->user->login = mx_strdup(tmp);
    mx_strdel(&tmp);
    tmp = mx_strnew(SERVER_INPUT_SIZE);
    mx_printstr("Input password-> ");
    mx_getch(tmp);
    c->user->password = mx_strdup(tmp);
    mx_strdel(&tmp);
    mx_client_create_request(c, 1);
}

void mx_client_register(t_client *c) {
    char *tmp = mx_strnew(SERVER_INPUT_SIZE);

    mx_printstr("Input login-> ");
    mx_getch(tmp);
    c->current_login = mx_strdup(c->user->login);
    c->user->login = mx_strdup(tmp);
    mx_strdel(&tmp);
    tmp = mx_strnew(SERVER_INPUT_SIZE);
    mx_printstr("Input password-> ");
    mx_getch(tmp);
    c->user->password = mx_strdup(tmp);
    mx_strdel(&tmp);
    tmp = mx_strnew(SERVER_INPUT_SIZE);
    mx_printstr("Input name-> ");
    mx_getch(tmp);
    c->user->name = mx_strdup(tmp);
    mx_strdel(&tmp);
    mx_printstr("Input surname-> ");
    tmp = mx_strnew(SERVER_INPUT_SIZE);
    mx_getch(tmp);
    c->user->surname = mx_strdup(tmp);
    mx_strdel(&tmp);
    tmp = mx_strnew(SERVER_INPUT_SIZE);
    mx_printstr("Input email-> ");
    mx_getch(tmp);
    c->user->email = mx_strdup(tmp);
    mx_strdel(&tmp);
    mx_client_request_register(c);
}

void mx_client_edit_user(t_client *c) {
    char *tmp = mx_strnew(SERVER_INPUT_SIZE);

    //c->user_copy = mx_copy_user_create(c->user);
    c->current_login = mx_strdup(c->user->login);
    c->user->status = mx_strdup("active");
    mx_printstr("Input login-> ");
    mx_getch(tmp);
    c->user->login = mx_strdup(tmp);
    mx_strdel(&tmp);
    tmp = mx_strnew(SERVER_INPUT_SIZE);
    mx_printstr("Input password-> ");
    mx_getch(tmp);
    c->user->password = mx_strdup(tmp);
    mx_strdel(&tmp);
    tmp = mx_strnew(SERVER_INPUT_SIZE);
    mx_printstr("Input name-> ");
    mx_getch(tmp);
    c->user->name = mx_strdup(tmp);
    mx_strdel(&tmp);
    mx_printstr("Input surname-> ");
    tmp = mx_strnew(SERVER_INPUT_SIZE);
    mx_getch(tmp);
    c->user->surname = mx_strdup(tmp);
    mx_strdel(&tmp);
    tmp = mx_strnew(SERVER_INPUT_SIZE);
    mx_printstr("Input email-> ");
    mx_getch(tmp);
    c->user->email = mx_strdup(tmp);
    mx_strdel(&tmp);
    mx_client_create_request(c, REQ_EDIT_USER);
}


void mx_client_parse_com(t_client *c, char *input_str) {

    if (!mx_strcmp(input_str, CLIENT_AUTORIZATION))
        mx_client_autorization(c);
    else if (!mx_strcmp(input_str, CLIENT_REGISTER))
        mx_client_register(c);
    else if (!mx_strcmp(input_str, CLIENT_EDIT_USER))
        mx_client_edit_user(c);
}

void mx_client_main(t_client **client) {
    t_client *c = *client;
    char *tmp = NULL;

    while(1) {
        tmp = mx_strnew(SERVER_INPUT_SIZE);
        mx_printstr("Input com-> ");
        mx_getch(tmp);
        mx_client_parse_com(c, tmp);
        mx_strdel(&tmp);
    }
}


int main(int argc, char *argv[]) {
    t_client *client = malloc(sizeof(t_client));
    client->user = malloc(sizeof(t_user_create));
    pthread_t recv_thread;

    if (argc != 3)
        mx_print_error("Usage ./uchat_client %IP adress %port\n", 1, true);
    mx_client_config_socket(&client, argv[1], argv[2]);
    //connect to server
    // mx_client_create_request(client, 0);
    // usleep(100);
    //pthread_create(&recv_thread, NULL, mx_recv_loop, (void*)&client);
    //mx_client_create_request(client, 1);
    // mx_client_create_request(client, 0);
    //mx_run_gtk((void*)&client);
    //pthread_join(recv_thread, NULL);
    mx_client_main(&client);
}



