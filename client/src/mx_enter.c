#include "uchat.h"

// static void wrong(GtkWidget *button, gpointer data) {
//     GtkWidget *window;
//     GtkWidget *label;
//     GtkWidget *button2;
//     GtkWidget *box;

//     window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//     gtk_window_set_title(GTK_WINDOW(window), "Ошибка ввода");
//     gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
//     gtk_window_set_modal(GTK_WINDOW(window), TRUE);
//     gtk_window_set_default_size(GTK_WINDOW(window),200, 100);
//     box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
//     gtk_container_add(GTK_CONTAINER(window), box);
//     gtk_container_set_border_width(GTK_CONTAINER(window), 20);
//     label = gtk_label_new("Вы допустили ошибку при вводе логина, или пароля.Повторите ввод.");
//     button2 = gtk_button_new_with_label("Ok");
//     g_signal_connect_swapped(button2, "clicked", G_CALLBACK(gtk_widget_destroy), window);
//     gtk_container_add(GTK_CONTAINER(box), label);
//     gtk_container_add(GTK_CONTAINER(box), button2);
//     gtk_widget_show_all(window);
//     gtk_main();
// }

static void print_hello(GtkWidget *button, gpointer data) {
//g_print ("Hello World\n");
    t_user *s = (t_user*)data;
    //int flag = 0;

    s->user = gtk_entry_get_text(GTK_ENTRY(s->euser));
    s->pass = gtk_entry_get_text(GTK_ENTRY(s->epass));
    s->sex = gtk_entry_get_text(GTK_ENTRY(s->sex1));
  // printf("%s\n%s\n%s\n", s->user, s->pass, s->sex);
   //запрашиваю по логину с базы данных пароль и сверяю с тем что в pass
   //если пароль совпал то mx_account , если нет то wrong
    mx_account(data);
}

void mx_enter(GtkApplication *app, gpointer data) {
    //GtkWidget *e_window;
    GtkWidget *user, *pass, *label;
    GtkWidget *button;
    GtkWidget *box;
    t_user *s = (t_user*)data;
   //t_user *s = (t_user*)malloc(sizeof(t_user));
    int length = 20;

    s->e_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(s->e_window), "Вход");
    gtk_window_set_position(GTK_WINDOW(s->e_window), GTK_WIN_POS_CENTER);
    gtk_window_set_modal(GTK_WINDOW(s->e_window), TRUE);
    gtk_window_set_default_size(GTK_WINDOW(s->e_window), 200, 200);
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_container_add(GTK_CONTAINER(s->e_window), box);
    gtk_container_set_border_width(GTK_CONTAINER(s->e_window), 20);
    user = gtk_label_new("Введите логин");
    pass = gtk_label_new("Введите пароль");
    label = gtk_label_new("Введите свой пол: m - для джентельменов, w - для леди");
    s->euser = gtk_entry_new();
    s->epass = gtk_entry_new();
    s->sex1 = gtk_entry_new(); //ЗАШИТЬ В СТРУКТУРУ
    gtk_entry_set_visibility(GTK_ENTRY(s->epass), FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(s->epass), '$');
    gtk_entry_set_max_length(GTK_ENTRY(s->euser), length);
    gtk_entry_set_max_length(GTK_ENTRY(s->epass), length);
    button = gtk_button_new_with_label("Ok");
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), s);
   // g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    //gtk_window_close(GTK_WINDOW(window));
  // printf("%d",1);
    gtk_container_add(GTK_CONTAINER(box), user);
   // printf("%d",2);
    gtk_container_add(GTK_CONTAINER(box), s->euser);
    gtk_container_add(GTK_CONTAINER(box), pass);
    gtk_container_add(GTK_CONTAINER(box), s->epass);
    gtk_container_add(GTK_CONTAINER(box), label);
    gtk_container_add(GTK_CONTAINER(box), s->sex1);
    gtk_container_add(GTK_CONTAINER(box), button);
    gtk_widget_show_all(s->e_window);
    gtk_main();

}
// 1 Не подключается
// 2 Подключить сверку с базой данных
//3 Сделать так чтобы закрывыались все окна и открывался акаунт
//4 Аудитор