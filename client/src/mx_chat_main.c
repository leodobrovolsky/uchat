#include "uchat.h"

static void messages(GtkWidget *button, gpointer data) {
    t_user *s = (t_user*)data;

    s->current = gtk_entry_get_text(GTK_ENTRY(s->chat_entry));
   // s->surname = gtk_entry_get_text(GTK_ENTRY(s->ap_entry2));
    gtk_label_set_text(GTK_LABEL(s->chat_label1), s->current);
   //gtk_label_set_text(GTK_LABEL(s->a_label6), s->surname);
    //gtk_widget_destroy(s->ap_window);
}

void mx_chat_main(GtkApplication* app, gpointer data) {
	t_user *s = (t_user*)data;
   // GtkWidget *chat_window;
    //GtkWidget *label1, *label2;
    GtkWidget *button1, *button2, *button3, *button4, *button_out, *mesage;
 //GtkWidget *entry;
    GtkWidget *box, *box1, *box2, *box3, *box4, /**button_box1, */ *button_box2;

    s->chat_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(s->chat_window), "ЧАТ");
    gtk_window_set_position(GTK_WINDOW(s->chat_window), GTK_WIN_POS_CENTER);
    gtk_window_set_modal(GTK_WINDOW(s->chat_window), TRUE);
    gtk_window_set_default_size(GTK_WINDOW(s->chat_window),850, 1000);
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    box1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    box2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    box3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    box4 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    button_box2 = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
    gtk_container_add(GTK_CONTAINER(s->chat_window), box);
	gtk_container_set_border_width(GTK_CONTAINER(s->chat_window), 20);
    if (s->current == NULL);
    else {
       s->chat_label1 = gtk_label_new(s->current);
    }
    //label1 = gtk_label_new("fgjhjjlkl;op");
    //label2 = gtk_label_new("cfgfhjkljhjk");
    s->chat_entry = gtk_entry_new();
    button1 = gtk_button_new_with_label("Все пользователи");
    button2 = gtk_button_new_with_label("Невролог");
    button3 = gtk_button_new_with_label("Хирург");
    button4 = gtk_button_new_with_label("бот");
    mesage = gtk_button_new_with_label("Отправить");
    button_out = gtk_button_new_with_label("Выйти");
    g_signal_connect(mesage, "clicked", G_CALLBACK(messages), s);
    //g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    //gtk_widget_destroy(window);
    gtk_container_add(GTK_CONTAINER(box1), button1);
    gtk_container_add(GTK_CONTAINER(box1), button2);
    gtk_container_add(GTK_CONTAINER(box1), button3);
    gtk_container_add(GTK_CONTAINER(box1), button4);
    gtk_container_add(GTK_CONTAINER(box2), s->chat_label1);
   // gtk_container_add(GTK_CONTAINER(box2), label2);
    gtk_container_add(GTK_CONTAINER(box3), s->chat_entry);
    gtk_container_add(GTK_CONTAINER(button_box2), mesage);
    gtk_container_add(GTK_CONTAINER(button_box2), button_out);
    gtk_container_add(GTK_CONTAINER(box3), button_box2);
    gtk_container_add(GTK_CONTAINER(box4), box1);
    gtk_container_add(GTK_CONTAINER(box4), box2);
    //gtk_container_add(GTK_CONTAINER(box), box4);
    gtk_box_pack_start(GTK_BOX(box), box4, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(box), box3);
    gtk_widget_hide(s->a_window);
    gtk_widget_show_all(s->chat_window);
    gtk_main();
}
