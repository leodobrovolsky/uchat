#include "uchat.h"

void mx_open_dialog(GtkWidget *button, void *void_client) {
    t_client *c = (t_client*)void_client;
    
    gtk_widget_show_all(c->but);
}


void gtk_loop(GtkWidget *window, void *void_client) {
    t_client *c = (t_client*)void_client;
    GtkWidget *button = NULL;
    GtkWidget *main = NULL;


    main = gtk_application_window_new(c->win);
    gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(main), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(main), "UCHAT");
    gtk_window_set_default_size(GTK_WINDOW(main), WINDOW_MAIN_WEIGHT, WINDOW_MAIN_HEIGHT);
    button = gtk_button_new_with_label("Open dialog");
    g_signal_connect(c->but, "clicked", G_CALLBACK(mx_open_dialog), c);
    gtk_widget_show_all(main);
}


void *mx_run_gtk(void *void_client) {
    t_client *c = *(t_client**)void_client;
    int status = 0;

    gtk_init(NULL, NULL);
    c->win = gtk_application_new(NULL, G_APPLICATION_FLAGS_NONE); 
    g_signal_connect(c->win, "activate", G_CALLBACK(gtk_loop), c);
    status = g_application_run(G_APPLICATION(c->win), 0, NULL);
    g_object_unref(c->win);
    return NULL;
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
    if (connect(c->sock_fd, (struct sockaddr *)&c->svaddr, sizeof(struct sockaddr_in)) == -1)
        mx_print_error("error connect\n", 1, true);
}





void mx_client_parse_json(t_client *main) {
    main = NULL;
    // t_client *c = *main;
    // char *str = mx_strdup(c->buf);
    // cJSON *root = cJSON_Parse(str);

    // if (!root || !root->child)
    //     mx_print_error_json(root);
    // root = root->child;
    // if (!root)
    //     mx_print_error_json(root);
    // root = root->next;
    // if (!root)
    //     mx_print_error_json(root);
    // if (!mx_strcmp(root->valuestring, JSON_TYPE_RESPONSE))
    //     mx_client_parse_response(main, root->next, root->prev->valueint);
    // else
    //     mx_print_error_json(root);
    // cJSON_Delete(root);
    // mx_strdel(&str);
}


void *mx_recv_loop(void *client) {
    t_client *c = *(t_client **)client;
    int size = 0;

    while(1) {
        c->buf = mx_strnew(SOCKET_BUFFER_SIZE);
        size = recv(c->sock_fd, c->buf, SOCKET_BUFFER_SIZE, 0);
        if (size > 0)
            mx_client_parse_json(c);
        mx_strdel(&c->buf);
    }
}

void mx_client_send(int fd, char *str) {
    send(fd, str, BUFFER_SIZE, 0);
}


void mx_create_req_connect(t_client *c) {
    char *str = mx_connect_request_to_json();

    mx_client_send(c->sock_fd, str);
}

void mx_client_create_request(t_client *client, int operation) {
    
    if (operation == REQ_CONNECT)
        mx_create_req_connect(client);
}


int main(int argc, char *argv[]) {
    t_client *client = malloc(sizeof(t_client));
    pthread_t recv_thread;

    if (argc != 3)
        mx_print_error("Usage ./uchat_client %IP adress %port\n", 1, true);
    mx_client_config_socket(&client, argv[1], argv[2]);
    //connect to server
    pthread_create(&recv_thread, NULL, mx_recv_loop, (void*)&client);
    mx_client_create_request(client, 1);
    //mx_run_gtk((void*)&client);
    pthread_join(recv_thread, NULL);
}



