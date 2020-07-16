#include "uchat.h"

int main (int argc, char **argv) {
    int status = 0;
    t_user *s = (t_user*)malloc(sizeof(t_user));

    gtk_init( &argc, &argv );
    s->app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE); //что это значит
    g_signal_connect(s->app, "activate", G_CALLBACK(mx_headband), s);
    status = g_application_run(G_APPLICATION(s->app), argc, argv); //что это не знаю но без этого окно не отображается
    g_object_unref(s->app); //что это зхначит освобождает память от обьекта гтк 
    return status;
}
