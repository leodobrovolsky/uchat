#include "uchat.h"

static void change(GtkWidget *button, gpointer data) {
    t_user *s = (t_user*)data;

    s->name = gtk_entry_get_text(GTK_ENTRY(s->ap_entry1));
    s->surname = gtk_entry_get_text(GTK_ENTRY(s->ap_entry2));
    gtk_label_set_text(GTK_LABEL(s->a_label4), s->name);
    gtk_label_set_text(GTK_LABEL(s->a_label6), s->surname);
    gtk_widget_destroy(s->ap_window);
}

static void delete(GtkWidget *button, gpointer data) {
    t_user *s = (t_user*)data;

    s->deth = 1;
}

static void print(GtkWidget *button, gpointer data) {
    t_user *s = (t_user*)data;
   // GtkWidget *ap_window;
    GtkWidget *label1, *label2;
    GtkWidget *button1;
    //GtkWidget *entry1, *entry2;
    GtkWidget *box;

    s->ap_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(s->ap_window), "Изменение профиля");
    gtk_window_set_position(GTK_WINDOW(s->ap_window), GTK_WIN_POS_CENTER);
    gtk_window_set_modal(GTK_WINDOW(s->ap_window), TRUE);
    gtk_window_set_default_size(GTK_WINDOW(s->ap_window),200, 100);
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_container_add(GTK_CONTAINER(s->ap_window), box);
    gtk_container_set_border_width(GTK_CONTAINER(s->ap_window), 20);
    label1 = gtk_label_new("Введите имя");
    label2 = gtk_label_new("Введите фамилию");
    s->ap_entry1 = gtk_entry_new();
    s->ap_entry2 = gtk_entry_new();
    button1 = gtk_button_new_with_label("Ok");
    g_signal_connect(button1, "clicked", G_CALLBACK(change), s);
    //g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    //gtk_widget_destroy(window);
    gtk_container_add(GTK_CONTAINER(box), label1);
    gtk_container_add(GTK_CONTAINER(box), s->ap_entry1);
    gtk_container_add(GTK_CONTAINER(box), label2);
    gtk_container_add(GTK_CONTAINER(box), s->ap_entry2);
    gtk_container_add(GTK_CONTAINER(box), button1);
    gtk_widget_show_all(s->ap_window);
    gtk_main();
}

void mx_account(gpointer data) {
    t_user *s = (t_user*)data;
    //GtkWidget *a_window;
    GtkWidget *button1, *button2, *button3, *button4;
    GtkWidget *button_box, *box, *box1, *box2, *box3;
    GtkWidget *image;
    GtkWidget *label1, *label2, *label3,  *label5;
    //int flag = 0;
    //GtkColorChooser *chooser = NULL;
    //GdkRGBA color = {0.0, 0.0, 0.0, 0.0};

    s->a_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    // if (s->deth == 1)
    //     gtk_widget_destroy(window);
    gtk_window_set_position(GTK_WINDOW(s->a_window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(s->a_window), "Профиль");
    gtk_window_set_default_size(GTK_WINDOW(s->a_window), 700, 1000);
    gtk_window_set_modal(GTK_WINDOW(s->a_window), TRUE);
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    button_box = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
    box1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);

   // gtk_window_set_position(GTK_WINDOW(box1), GTK_WIN_POS_CENTER);
    box2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    box3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_box_set_spacing(GTK_BOX(button_box), 10);
    gtk_container_add(GTK_CONTAINER(s->a_window), box);
    gtk_container_set_border_width(GTK_CONTAINER(s->a_window), 20);
    button1 = gtk_button_new_with_label ("Изменить имя или фамилию");
    button2 = gtk_button_new_with_label ("Удалить профиль");
    button3 = gtk_button_new_with_label("Перейти в чат");
    button4 = gtk_button_new_with_label("Выйти");
    // if (s->deth == 1)
    //     gtk_widget_destroy(window);
    label1 = gtk_label_new("Логин");
    label2 = gtk_label_new(s->user);
    label3 = gtk_label_new("Имя");
    if (s->name == NULL)
        s->a_label4 = gtk_label_new("");
    else 
        s->a_label4 = gtk_label_new(s->name);
    label5 = gtk_label_new("Фамилия");
    if (s->surname == NULL)
        s->a_label6 = gtk_label_new("");
    else
        s->a_label6 = gtk_label_new(s->surname);
    if ((s->sex)[0] == 'w')
        image = gtk_image_new_from_file("avatar3.jpg");
    else
        image = gtk_image_new_from_file("avatar4.jpg");
    g_signal_connect(button1, "clicked", G_CALLBACK(print), s);
    g_signal_connect(button2, "clicked", G_CALLBACK(delete), s);
    g_signal_connect(button3, "clicked", G_CALLBACK(mx_chat_main), s);
   // g_signal_connect_swapped(button3, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    gtk_container_add(GTK_CONTAINER(box), image);
    gtk_container_add(GTK_CONTAINER(box1), label1);
    gtk_container_add(GTK_CONTAINER(box1), label2);
    gtk_container_add(GTK_CONTAINER(box2), label3);
    gtk_container_add(GTK_CONTAINER(box2), s->a_label4);
    gtk_container_add(GTK_CONTAINER(box3), label5);
    gtk_container_add(GTK_CONTAINER(box3), s->a_label6);
    gtk_container_add(GTK_CONTAINER(button_box), button1);
    gtk_container_add(GTK_CONTAINER(button_box), button2);
    gtk_container_add(GTK_CONTAINER(button_box), button3);
    gtk_container_add(GTK_CONTAINER(button_box), button4);
     //gtk_box_set_center_widget(GTK_BOX(box), box1);
    gtk_container_add(GTK_CONTAINER(box), box1);
     //gtk_window_set_position(GTK_WINDOW(GTK_WIDGET(box1)), GTK_WIN_POS_CENTER);
    gtk_container_add(GTK_CONTAINER(box), box2);
    gtk_container_add(GTK_CONTAINER(box), box3);
    gtk_container_add(GTK_CONTAINER(box), button_box);


    //gtk_widget_destroy(s->main_window);
    //gtk_widget_destroy(s->e_window);
    gtk_widget_hide(s->main_window);
    gtk_widget_hide(s->e_window);

    gtk_widget_show_all(s->a_window);
}

//1 Центрировать имя фамилию логин
//2 Сделать удаление профиля
//3 Cделать функционал кнопки  выйти
//4 Аудитор