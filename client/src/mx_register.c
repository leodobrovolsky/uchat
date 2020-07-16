#include "uchat.h"

static void wrong(GtkWidget *button, gpointer data, t_user *s) {
    GtkWidget *window;
    GtkWidget *label;
    GtkWidget *button2;
    GtkWidget *box;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Ошибка ввода");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_modal(GTK_WINDOW(window), TRUE);
    gtk_window_set_default_size(GTK_WINDOW(window),200, 100);
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_container_set_border_width(GTK_CONTAINER(window), 20);
    label = gtk_label_new("");
    if (s->fl == 1)
        gtk_label_set_text(GTK_LABEL(label), "Вы допустили ошибку при вводе логина. Возможно ваш логин не уникален, замените его. Повторите ввод.");
    if (s->fl == 2)
        gtk_label_set_text(GTK_LABEL(label), "Вы допустили ошибку при вводе пароля. Повторите ввод.");
    if (s->fl == 3)
        gtk_label_set_text(GTK_LABEL(label), "Вы допустили ошибку при вводе почты. Повторите ввод.");
    if (s->fl == 4)
        gtk_label_set_text(GTK_LABEL(label), "Ваш пароль не совпадает с повторным введением пароля. Повторите ввод.");
    button2 = gtk_button_new_with_label("Ok");
    g_signal_connect_swapped(button2, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    gtk_container_add(GTK_CONTAINER(box), label);
    gtk_container_add(GTK_CONTAINER(box), button2);
    gtk_widget_show_all(window);
    gtk_main();
}

static void close_right(GtkWidget *button, gpointer data) {
    t_user *s = (t_user*)data;

    gtk_widget_destroy(s->reg_right_wind);
    gtk_widget_destroy(s->reg_window);

}

static void rigth(GtkWidget *button, gpointer data) {
    //GtkWidget *window;
    GtkWidget *label;
    GtkWidget *button1;
    GtkWidget *box;
    t_user *s = (t_user*)data;

    s->reg_right_wind = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(s->reg_right_wind), "Коррректный ввод");
    gtk_window_set_position(GTK_WINDOW(s->reg_right_wind), GTK_WIN_POS_CENTER);
    gtk_window_set_modal(GTK_WINDOW(s->reg_right_wind), TRUE);
    gtk_window_set_default_size(GTK_WINDOW(s->reg_right_wind),100, 100);
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_container_add(GTK_CONTAINER(s->reg_right_wind), box);
    gtk_container_set_border_width(GTK_CONTAINER(s->reg_right_wind), 20);
    label = gtk_label_new("Вводные данные приняты! Ввойдите в приложение");
    button1 = gtk_button_new_with_label("Ok");
    g_signal_connect(button1, "clicked", G_CALLBACK(close_right), s); //КАК СЮДА ВТУЛИТЬ ЕЩЕ ПЕРЕЗАПУСК MX_REGISTER
    gtk_container_add(GTK_CONTAINER(box), label);
    gtk_container_add(GTK_CONTAINER(box), button1);
    gtk_widget_show_all(s->reg_right_wind);
    gtk_main();
//  GtkWidget *dialog, *label, *content_area; 
//  GtkDialogFlags flags;
//  GtkWidget *window;

// flags = GTK_DIALOG_DESTROY_WITH_PARENT;
// window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//  dialog = gtk_dialog_new_with_buttons("Коррректный ввод", GTK_WINDOW(window), flags, ("OK"), GTK_RESPONSE_NONE, NULL); //ЕСТЬ ВОПРОСЫ
//  content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog)); 
//  label = gtk_label_new("Вводные данные приняты! Ввойдите в приложение");
// g_signal_connect_swapped(dialog, "response", G_CALLBACK(gtk_widget_destroy), dialog);
//  gtk_container_add(GTK_CONTAINER(content_area), label); 
//  gtk_widget_show_all(dialog); 

}

static void print_hello(GtkWidget *button, gpointer data) {
//g_print ("Hello World\n");
    t_user *s = (t_user*)data;
    int flag = 0;

    s->user = gtk_entry_get_text(GTK_ENTRY(s->euser));
    s->pass = gtk_entry_get_text(GTK_ENTRY(s->epass));
    s->pass2 = gtk_entry_get_text(GTK_ENTRY(s->epass2));
    s->email1 = gtk_entry_get_text(GTK_ENTRY(s->email));
   //printf("%s\n%s\n%s\n%s\n", s->user, s->pass, s->pass2, s->email1);
    if (mx_strcmp(s->pass, s->pass2) != 0) {
        flag = 1;
        s->fl = 4;
    }
    if (!mx_valid(s->user, 1)) {
        s->fl = 1;
        flag = 1;
    }
    if (!mx_valid(s->pass, 2)) {
        s->fl = 2;
        flag = 1;
    }
    if (!mx_valid(s->email1, 3)) {
        s->fl = 3;
       flag = 1;
    }
    if (flag != 0)
        wrong(button, data, s);
    if (flag == 0)
        rigth(button, data);
}

void mx_register(GtkApplication* app, gpointer data) {
    //GtkWidget *window;
    GtkWidget *luser, *lpass, *lpass2, *lemail;
    GtkWidget *button;
    GtkWidget *box;
    t_user *s = (t_user*)data;
    int length = 20;

    s->reg_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(s->reg_window), "Регистрация");
    gtk_window_set_position(GTK_WINDOW(s->reg_window), GTK_WIN_POS_CENTER);
    gtk_window_set_modal(GTK_WINDOW(s->reg_window), TRUE);
    gtk_window_set_default_size(GTK_WINDOW(s->reg_window), 400, 400);
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_container_add(GTK_CONTAINER(s->reg_window), box);
    gtk_container_set_border_width(GTK_CONTAINER(s->reg_window), 20);
    luser = gtk_label_new("Введите логин");
    lpass = gtk_label_new("Введите пароль");
    lpass2 = gtk_label_new("Введите пароль eще раз");
    lemail = gtk_label_new("Введите емейл");
    s->euser = gtk_entry_new();
    s->epass = gtk_entry_new();
    s->epass2 = gtk_entry_new();
    s->email = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(s->epass), FALSE);
    gtk_entry_set_visibility(GTK_ENTRY(s->epass2), FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(s->epass), '$');
    gtk_entry_set_invisible_char(GTK_ENTRY(s->epass2), '$');
    gtk_entry_set_max_length(GTK_ENTRY(s->euser), length);
    gtk_entry_set_max_length(GTK_ENTRY(s->epass), length);
    gtk_entry_set_max_length(GTK_ENTRY(s->epass2), length);
    gtk_entry_set_max_length(GTK_ENTRY(s->email), length);
    button = gtk_button_new_with_label("Ok");
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), s);
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), s->reg_window);
    gtk_container_add(GTK_CONTAINER(box), luser);
    gtk_container_add(GTK_CONTAINER(box), s->euser);
    gtk_container_add(GTK_CONTAINER(box), lpass);
    gtk_container_add(GTK_CONTAINER(box), s->epass);
    gtk_container_add(GTK_CONTAINER(box), lpass2);
    gtk_container_add(GTK_CONTAINER(box), s->epass2);
    gtk_container_add(GTK_CONTAINER(box), lemail);
    gtk_container_add(GTK_CONTAINER(box), s->email);
    gtk_container_add(GTK_CONTAINER(box), button);
    gtk_widget_show_all(s->reg_window);
    gtk_main();
}



//3 Связь с базой данных
//4 Аудитор
//5 Разобраться с rigth()