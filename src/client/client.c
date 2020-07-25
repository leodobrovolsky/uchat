#include "uchat.h"

void mx_open_dialog(GtkWidget *button, void *void_client) {
    t_client_main *c = (t_client_main*)void_client;
    
    gtk_widget_show_all(c->but);
}


void gtk_loop(GtkWidget *window, void *void_client) {
    t_client_main *c = (t_client_main*)void_client;
    GtkWidget *button = NULL;
    GtkWidget *main = NULL;


    main = gtk_application_window_new(c->win);
    gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(main), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(main), "UCHAT");
    gtk_window_set_default_size(GTK_WINDOW(main), WINDOW_MAIN_WEIGHT, WINDOW_MAIN_HEIGHT);
    button = gtk_button_new_with_label ("Open dialog");
    g_signal_connect(c->but, "clicked", G_CALLBACK(mx_open_dialog), c);   
    gtk_widget_show_all(main);
}


void *mx_run_gtk(void *void_client) {
    t_client_main *c = (t_client_main*)void_client;
    int status = 0;

    c = malloc(sizeof(t_client_main));
    gtk_init(NULL, NULL);
    c->win = gtk_application_new(NULL, G_APPLICATION_FLAGS_NONE); 
    g_signal_connect(c->win, "activate", G_CALLBACK(gtk_loop), c);
    status = g_application_run(G_APPLICATION(c->win), 0, NULL);
    g_object_unref(c->win);
    return NULL;
}











int main(int argc, char *argv[]) {
    void *client = NULL;
    pthread_t thread_send = 0;
    pthread_t thread_recv = 0;

    if (argc != 3)
        mx_print_error("Usage ./uchat_client %IP adress %port\n", 1, true);

    //connect to server

    mx_run_gtk((void*)client);
}
