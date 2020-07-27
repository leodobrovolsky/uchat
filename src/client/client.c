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
    t_client *c = (t_client*)void_client;
    int status = 0;

    gtk_init(NULL, NULL);
    c->win = gtk_application_new(NULL, G_APPLICATION_FLAGS_NONE); 
    g_signal_connect(c->win, "activate", G_CALLBACK(gtk_loop), c);
    status = g_application_run(G_APPLICATION(c->win), 0, NULL);
    g_object_unref(c->win);
    return NULL;
}




void mx_client_config_socket(t_client **client, char *IP, char *port) {
    struct sockaddr_in svaddr;

    *(client->sock_fd) = socket(AF_INET, SOCK_STREAM, 0);
    if (*(client->sock_fd) < 0)
        mx_print_error("Error create socket", 1, true);
    serv = gethostbyname(s->argv[1]);    
    if(!serv) {
        write(2, "uchat error:: no host\n", 22);
        exit(1);
    }

    mx_memset(&svaddr, 0, sizeof(struct sockaddr_in));
    svaddr.sin_family = AF_INET;
    mx_strncpy((char*)&svaddr.sin_addr.s_addr,(char*)serv->h_addr,serv->h_length);
    svaddr.sin_port = htons(mx_atoi(s->argv[2])); //можна
    
    if (inet_pton(AF_INET, s->argv[1], &svaddr.sin_addr) <= 0)
    ; //можна
    //ошибка адреса
    if (connect(sfd, (struct sockaddr *)&svaddr, sizeof(struct sockaddr_in)) == -1){
        write(2, "ошибка установления соединения", 30);
        exit(1);
    }
    else {
        printf("%s ", "uchat:: \033[0;32mConnected to server\033[0;32m");
        printf("%s : %s\n", s->argv[1], s->argv[2]);
    }
    s->sfd = sfd;	
}






int main(int argc, char *argv[]) {
    t_client *client = malloc(sizeof(t_client));
    pthread_t pthread;

    mx_client_config_socket(&client, argv[1], argv[2]);

    if (argc != 3)
        mx_print_error("Usage ./uchat_client %IP adress %port\n", 1, true);

    //connect to server

    mx_run_gtk((void*)client);
}
