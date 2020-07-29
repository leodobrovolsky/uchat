#include "uchat.h"
// #include <gtk/gtk.h>

// #define IMAGE_USER_1 user1.jpg

#define MIN_COUNT_FORM 5
#define MAX_COUNT_FORM 20


// //мой



// static GtkWidget *make_box( gboolean homogeneous,
//                             gint     spacing,
//                             gboolean expand,
//                             gboolean fill,
//                             guint    padding ) 

// static void print_hello (GtkWidget *widget, gpointer data)
// {
//   g_print ("click box\n");
// }

void mx_open_dialog(GtkWidget *button, void *void_client) {
    t_client *c = (t_client*)void_client;
    
    gtk_widget_show_all(c->but);
}

// GtkWidget *user, *pass;
//     GtkWidget *button_1;
//     GtkWidget *box_left, *box_center, *box_right, *frame;
//     GtkWidget *log1, *log2, *log3, *log4;
//     GtkWidget *label, *label1, *label2, *label3, *label4;

//     main = gtk_application_window_new(c->win);
//     gtk_window_new(GTK_WINDOW_TOPLEVEL);
//     gtk_window_set_position(GTK_WINDOW(main), GTK_WIN_POS_CENTER);
//     gtk_window_set_title(GTK_WINDOW(main), "UCHAT");
//     gtk_window_set_default_size(GTK_WINDOW(main), WINDOW_MAIN_WEIGHT, WINDOW_MAIN_HEIGHT);

//     button = gtk_button_new_with_label ("Open dialog");
//     g_signal_connect(c->but, "clicked", G_CALLBACK(mx_open_dialog), c);   

//     //mycode
//     GtkCssProvider *provider = gtk_css_provider_new();
//     GtkStyleContext *context = gtk_widget_get_style_context(box_left);
//     gtk_css_provider_load_from_data(GTK_CSS_PROVIDER(provider), "* {\n background-color: RGB(4,9,82);\n }\n", -1, NULL); //темний
//     gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

//     // t_user *s = (t_user*)data;
//     // label = gtk_label_new("Это пример виджета метки");
//     label = gtk_label_new("Логин");
//     label1 = gtk_label_new("ROOM1");
//     label2 = gtk_label_new("ROOM2");

//     box_left = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
//     box_center = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
//     box_right = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

//     log1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
//     log2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

static void get_style(void) {
    GdkScreen *screen;
    GdkDisplay *display;
    GtkCssProvider *provider;

    const char *css_style_file = "style.css";
    GFile *css_fp = g_file_new_for_path(css_style_file);
    GError *error = 0;

    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);

    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    gtk_css_provider_load_from_file(provider, css_fp, &error);

    g_object_unref(provider);
}


void gtk_loop(GtkWidget *window, void *void_client) {
    t_client *c = (t_client*)void_client;
    GtkWidget *button = NULL;
    GtkWidget *main = NULL;

    GtkWidget *user, *pass;
    GtkWidget *button_1, *button_2;
    GtkWidget *box_left, *box_bottom_center, *box_center, *box_right, *label, *boxnew, *label2, *label3, *label4, *label5, *label6, *box, *button_send;
    GtkWidget *button1, *button2, *button3, *button4, *button_out, *mesage, *box_mesages, *u_name, *box_meng, *box_user_msg1, *box_user_msg2;
    GtkWidget *box_user_msg3, *box_user_msg4, *box_user_msg5, *box_user_msg6, *box_user_msg7;
    GtkWidget *label7, *label8, *label9, *label10, *label11, *label12, *label13, *label14;
    GtkWidget *box_user_in_room, *box_user_in_room2;
    GtkWidget *grid;

    get_style();

    main = gtk_application_window_new(c->win);
    gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(main), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(main), "UCHAT");
    gtk_window_set_default_size(GTK_WINDOW(main), WINDOW_MAIN_WEIGHT, WINDOW_MAIN_HEIGHT);

    

    // button = gtk_button_new_with_label ("Open dialog");
    // g_signal_connect(c->but, "clicked", G_CALLBACK(mx_open_dialog), c);   

    //mycode
    // GtkCssProvider *provider = gtk_css_provider_new();
    // GtkStyleContext *context = gtk_widget_get_style_context(box_left);
    // gtk_css_provider_load_from_data(GTK_CSS_PROVIDER(provider), "* {\n background-color: RGB(4,9,82);\n }\n", -1, NULL); //темний
    // gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    // t_user *s = (t_user*)data;
    // label = gtk_label_new("Это пример виджета метки");
    label = gtk_label_new("Логин");
    label2 = gtk_label_new("wind");
    label3 = gtk_label_new("user");
    label4 = gtk_label_new("dop");
    label5 = gtk_label_new("messg user 1");
    label6 = gtk_label_new("messg user 2");
    label7 = gtk_label_new("messg user 3");
    label8 = gtk_label_new("messg user 4");
    label9 = gtk_label_new("messg user 5");
    label10 = gtk_label_new("messg user 6");
    label11 = gtk_label_new("Ivan");
    label12 = gtk_label_new("Mykola");
    label13 = gtk_label_new("messg user 7");

    // label1 = gtk_label_new("ROOM1");
    box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    // box_left = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    // box_center = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    // box_right = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    // boxnew = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    // button_2 = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
    mesage = gtk_button_new_with_label("Отправить");
    // log1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    // gtk_container_set_border_width(GTK_CONTAINER(box_left), 0);


    button1 = gtk_button_new_with_label("Все пользователи"); //левое окно
    button2 = gtk_button_new_with_label("Сообщения");
    button3 = gtk_button_new_with_label("USERS");
    button4 = gtk_button_new_with_label("sdfsdfsdfsdfsdf");
    mesage = gtk_button_new_with_label("Отправить2");
    button_send = gtk_button_new_with_label("Отправить");

    GtkStyleContext *context;
    context = gtk_widget_get_style_context(button1);
    gtk_style_context_add_class(context,"button1");

    GtkWidget *us1, *us2, *us3, *us4, *us5, *us6;

    us1 = gtk_button_new_with_label("Комнаты");
    us2 = gtk_button_new_with_label("Комната2");
    us3 = gtk_button_new_with_label("Комната3");
    us4 = gtk_button_new_with_label("MESAGES");
    us5 = gtk_button_new_with_label("Комната4");
    us6 = gtk_button_new_with_label("Управление");
    // g_signal_connect(button1, "clicked", G_CALLBACK(NULL), box_left);


    // gtk_container_add(GTK_CONTAINER(main), box);
    // gtk_container_add(GTK_CONTAINER(box), box_left);
    // gtk_container_add(GTK_CONTAINER(box), box_center);
    // gtk_container_add(GTK_CONTAINER(box), box_right);

    // gtk_container_add(GTK_CONTAINER(box), box_right);
    
    // gtk_container_add(GTK_CONTAINER(box_left), button1);
    // gtk_container_add(GTK_CONTAINER(box_center), button2);
    //  gtk_container_add(GTK_CONTAINER(box_right), button3);
    // gtk_container_add(GTK_CONTAINER(box_left), label2);
    // gtk_container_add(GTK_CONTAINER(box_center), label3);
    // gtk_container_add(GTK_CONTAINER(box_left), label3);

    // gtk_box_get_baseline_position (GTK_BOX(box_left));
    // gtk_box_set_spacing(GTK_BOX(box_left), 0);
    // gtk_box_set_spacing(GTK_BOX(box_center), 0); //между элементами
    // gtk_box_set_spacing(GTK_BOX(box_right), 0);
    // gtk_box_set_homogeneous(GTK_BOX(box_left), TRUE); //привести к одинаковому рзмеру все содержимое
    // gtk_box_set_homogeneous(GTK_BOX(box_right), TRUE);

    // gtk_box_pack_start (GTK_BOX (box), gtk_label_new ("login"), 1, 1, 0);
    // gtk_box_pack_start (GTK_BOX (box), gtk_button_new_with_label("window"), TRUE, TRUE, 0);
    // gtk_box_pack_start (GTK_BOX (box), gtk_button_new_with_label("users"), 1, 1, 0);

    box = gtk_fixed_new ();
    gtk_container_add (GTK_CONTAINER (main), box);
    gtk_widget_show (box);

    // gtk_fixed_put(GTK_FIXED(box), box_left, 0, 0);
    // gtk_fixed_put(GTK_FIXED(box), box_center, 200, 70);
    // gtk_fixed_put(GTK_FIXED(box), button3, 800, 70);
    // gtk_widget_set_opacity(box_left, 0.0);
    // gtk_widget_set_size_request(button1, 200, 700);
    // gtk_widget_set_size_request(box_center, 600, 530);
    // gtk_widget_set_size_request(button3, 200, 630);

    box_left = gtk_fixed_new ();
    gtk_container_add (GTK_CONTAINER (box), box_left);
    gtk_fixed_put(GTK_FIXED(box), box_left, 0, 0);
    gtk_widget_set_size_request(box_left, 200, 700);
    gtk_widget_show (box_left);

    box_center = gtk_fixed_new ();
    gtk_container_add (GTK_CONTAINER (box), box_center);
    gtk_widget_show (box_center);
    gtk_fixed_put(GTK_FIXED(box), box_center, 200, 70);
    gtk_widget_set_size_request(box_center, 600, 530);

    box_right = gtk_fixed_new ();
    gtk_container_add (GTK_CONTAINER (box), box_right);
    gtk_widget_show (box_right);
    gtk_fixed_put(GTK_FIXED(box), box_right, 800, 70);
    gtk_widget_set_size_request(box_right, 200, 630);

    gtk_fixed_put(GTK_FIXED(box_left), us1, 0, 0);
    gtk_fixed_put(GTK_FIXED(box_left), us2, 0, 70);
    gtk_fixed_put(GTK_FIXED(box_left), us3, 0, 140);
    gtk_fixed_put(GTK_FIXED(box_left), us5, 0, 210);
    // gtk_fixed_put(GTK_FIXED(box_left), us5, 0, 280);
    // gtk_widget_set_opacity(box_left, 0.0);
    gtk_widget_set_size_request(us1, 200, 70);
    gtk_widget_set_size_request(us2, 200, 70);
    gtk_widget_set_size_request(us3, 200, 70);
    gtk_widget_set_size_request(us4, 200, 70);
    gtk_widget_set_size_request(us5, 200, 70);


    //нижник блок меседжы

    box_bottom_center = gtk_fixed_new ();
    gtk_container_add (GTK_CONTAINER (box), box_bottom_center);

    gtk_widget_show (box_bottom_center);
    gtk_fixed_put(GTK_FIXED(box_left), us4, 200, 600);
    gtk_widget_set_size_request(us4, 600, 100);
    gtk_widget_show (box_bottom_center);

    // box_mesages = gtk_fixed_new ();
    // gtk_container_add (GTK_CONTAINER (box), box_mesages);
    // gtk_widget_show (box_mesages);

    GtkWidget *text;

    box_mesages = gtk_fixed_new ();
    gtk_container_add (GTK_CONTAINER (box_bottom_center), box_mesages);
    // gtk_entry_set_placeholder_text (GTK_ENTRY (us5), "Сообщения"); /* imposto il testo trasparente che scompare quando clicco o scrivo */

    text = gtk_entry_new();
    gtk_entry_set_max_length (GTK_ENTRY (text), 0);
    gtk_entry_set_width_chars (GTK_ENTRY (text), 37);
    gtk_entry_set_placeholder_text(GTK_ENTRY (text), "Send a message");
    gtk_fixed_put(GTK_FIXED(box_mesages), text, 250, 625);
    gtk_widget_set_size_request(text, 350, 50);
    // gtk_box_pack_start (GTK_BOX (box_mesages), gtk_label_new ("login"), 1, 1, 0);
    // gtk_box_pack_start (GTK_BOX (box_mesages), gtk_button_new_with_label("window"), TRUE, TRUE, 0);

    gtk_widget_show (box_mesages);

    gtk_fixed_put(GTK_FIXED(box), box_mesages, 230, 600);
    gtk_widget_set_size_request(box_mesages, 600, 100);
    gtk_widget_show (box_mesages);
    gtk_fixed_put(GTK_FIXED(box_mesages), button_send, 630, 625);
    gtk_widget_set_size_request(button_send, 100, 50);

    box_meng = gtk_fixed_new ();
    gtk_container_add (GTK_CONTAINER (box), box_meng);
    gtk_widget_show (box_meng);
    gtk_fixed_put(GTK_FIXED(box_meng), us6, 200, 0);
    gtk_widget_set_size_request(us6, 800, 70);
    gtk_widget_show (box_meng);

    box_user_msg1 = gtk_fixed_new ();
    gtk_container_add (GTK_CONTAINER (box_center), box_user_msg1);
    gtk_widget_show (box_user_msg1);
    gtk_fixed_put(GTK_FIXED(box_user_msg1), label5, 225, 100);
    gtk_widget_set_size_request(label5, 550, 75);
    gtk_widget_show (box_user_msg1);

    box_user_msg2 = gtk_fixed_new ();
    gtk_container_add (GTK_CONTAINER (box_center), box_user_msg2);
    gtk_widget_show (box_user_msg2);
    gtk_fixed_put(GTK_FIXED(box_user_msg2), label6, 225, 175);
    gtk_widget_set_size_request(label6, 550, 75);
    gtk_widget_show (box_user_msg2);

    box_user_msg3 = gtk_fixed_new ();
    gtk_container_add (GTK_CONTAINER (box_center), box_user_msg3);
    gtk_widget_show (box_user_msg3);
    gtk_fixed_put(GTK_FIXED(box_user_msg3), label7, 225, 250);
    gtk_widget_set_size_request(label7, 550, 75);
    gtk_widget_show (box_user_msg3);

    box_user_msg4 = gtk_fixed_new ();
    gtk_container_add (GTK_CONTAINER (box_center), box_user_msg4);
    gtk_widget_show (box_user_msg4);
    gtk_fixed_put(GTK_FIXED(box_user_msg4), label8, 225, 325);
    gtk_widget_set_size_request(label8, 550, 75);
    gtk_widget_show (box_user_msg4);

    box_user_msg5 = gtk_fixed_new ();
    gtk_container_add (GTK_CONTAINER (box_center), box_user_msg5);
    gtk_widget_show (box_user_msg5);
    gtk_fixed_put(GTK_FIXED(box_center), box_user_msg5, 225, 400);//установка размера бокса
    gtk_widget_set_size_request(box_user_msg5, 550, 75);//тут установил размер бокса
    gtk_fixed_put(GTK_FIXED(box_user_msg5), label9, 225, 400);//установка расположения лебла и где
    gtk_widget_set_size_request(label9, 550, 75);//тут установил размер лейбла
    gtk_widget_show (box_user_msg5);

    box_user_msg6 = gtk_fixed_new ();
    gtk_container_add (GTK_CONTAINER (box_center), box_user_msg6);
    gtk_fixed_put(GTK_FIXED(box_user_msg6), label10, 225, 475);
    gtk_widget_set_size_request(label10, 550, 75);
    gtk_widget_show (box_user_msg6);

    box_user_in_room = gtk_fixed_new ();
    gtk_container_add (GTK_CONTAINER (box_right), box_user_in_room);

    gtk_fixed_put(GTK_FIXED(box_right), box_user_in_room, 800, 70); //установка размера бокса
    gtk_widget_set_size_request(box_user_in_room, 200, 100); //тут установил размер бокса
    gtk_fixed_put(GTK_FIXED(box_user_in_room), label11, 800, 70);
    gtk_widget_set_size_request(label11, 200, 70);
    gtk_widget_show (box_user_in_room);

    box_user_in_room2 = gtk_fixed_new ();
    gtk_container_add (GTK_CONTAINER (box_right), box_user_in_room2);
    gtk_fixed_put(GTK_FIXED(box_right), box_user_in_room2, 800, 140); //установка размера бокса
    gtk_widget_set_size_request(box_user_in_room2, 200, 100); //тут установил размер бокса
    gtk_fixed_put(GTK_FIXED(box_user_in_room2), label12, 800, 140);
    gtk_widget_set_size_request(label12, 200, 70);
    gtk_widget_show (box_user_in_room2);




    // g_signal_connect (box_user_msg1, "clicked", G_CALLBACK (print_hello), NULL);

//     grid = gtk_grid_new ();
//     gtk_grid_set_row_spacing (GTK_GRID (grid), 100);

// /* Pack the container in the window */
//     gtk_container_add (GTK_CONTAINER (box_mesages), grid);
//     GtkWidget *label_user = gtk_label_new("Логин     ");
//     u_name  = gtk_entry_new();
//     gtk_entry_set_placeholder_text (GTK_ENTRY (u_name), "Логин"); /* imposto il testo trasparente che scompare quando clicco o scrivo */
//     gtk_grid_attach (GTK_GRID (grid), label_user , 0, 0, 1, 1);
//     gtk_grid_attach (GTK_GRID (grid), u_name, 1, 0, 1, 1);
//     gtk_widget_show (grid);


    

    // gtk_fixed_put(GTK_FIXED(box), box_center, 700, 0);
    // gtk_widget_set_opacity(box_center, 0.0);
    // gtk_widget_set_size_request(box_center, 700, 700);


    // GtkWidget *grid, *child1, *child2, *log1 ;

    // grid = gtk_grid_new ();
    // gtk_grid_set_row_spacing (GTK_GRID (grid), 3);
    // // gtk_container_add (GTK_CONTAINER (box_center), grid);

    // // child1 = gtk_label_new ("Два");
    // // gtk_widget_set_hexpand (button4 , TRUE);
    // // gtk_widget_set_halign (button4 , GTK_ALIGN_FILL);
    // gtk_grid_attach (GTK_GRID (grid), button2, 1, 0, 2, 1);
    // gtk_grid_attach_next_to (GTK_GRID (grid), button3, button1, GTK_POS_BOTTOM, 1, 2);
    // gtk_grid_attach_next_to (GTK_GRID (grid), button4, button3, GTK_POS_RIGHT, 2, 1);
    // gtk_grid_attach (GTK_GRID (grid), button2, 1, 2, 1, 1);

    // child2 = gtk_label_new ("Два");
    // gtk_widget_set_hexpand (child2, TRUE);
    // gtk_widget_set_halign (child1, GTK_ALIGN_FILL);
    // gtk_grid_attach_next_to (GTK_GRID (grid), child2, child1, GTK_POS_RIGHT, 1, 1);
    

    gtk_widget_show(button1);
    
   


    // gtk_container_add(GTK_CONTAINER(box_left), button1);
    // gtk_container_add(GTK_CONTAINER(box_left), box_center);
    // gtk_container_add(GTK_CONTAINER(box_left), label2);
    // gtk_container_add(GTK_CONTAINER(box_left), label3);
    // gtk_container_add(GTK_CONTAINER(box_left), button2);
    // gtk_container_add(GTK_CONTAINER(box_left), button3);

    // gtk_container_add(GTK_CONTAINER(box_right), button_2);
    // gtk_container_add(GTK_CONTAINER(boxnew), box_left);
    // gtk_container_add(GTK_CONTAINER(boxnew), box_center);

    // gtk_box_pack_start(GTK_BOX(box), boxnew, TRUE, TRUE, 0);
    // gtk_container_add(GTK_CONTAINER(box), box_right);
    // button_1 = gtk_button_new_with_label ("Зарегистрироваться");
    // g_signal_connect(button_1, "clicked", G_CALLBACK(NULL), box_left);
    
    // gtk_container_add(GTK_CONTAINER(box_left), button_1);
    

    // gtk_box_pack_start (GTK_BOX (box), gtk_label_new ("Окно"), TRUE, FALSE, 0);
    // gtk_box_pack_start (GTK_BOX (box), gtk_label_new ("Юзеры"), TRUE, TRUE, 0);

    // GtkWidget *grid, *child1, *child2, *log1 ;

    // grid = gtk_grid_new ();
    // gtk_grid_set_row_spacing (GTK_GRID (grid), 3);
    // gtk_container_add (GTK_CONTAINER (box_center), grid);

    // // child1 = gtk_label_new ("Два");
    // gtk_widget_set_hexpand (button4 , TRUE);
    // gtk_widget_set_halign (button4 , GTK_ALIGN_FILL);
    // gtk_grid_attach (GTK_GRID (grid), button4, 0, 0, 1, 1);
    // gtk_grid_attach (GTK_GRID (grid), mesage, 0, 0, 1, 1);

    // child2 = gtk_label_new ("Два");
    // gtk_widget_set_hexpand (child2, TRUE);
    // gtk_widget_set_halign (child1, GTK_ALIGN_FILL);
    // gtk_grid_attach_next_to (GTK_GRID (grid), child2, child1, GTK_POS_RIGHT, 1, 1);


//   gtk_container_add(GTK_CONTAINER(box_left), label);
//   gtk_container_add(GTK_CONTAINER(log1), label1);
    
    // gtk_container_add(GTK_CONTAINER(box_left), button);
    
    

    // GtkWidget *box;
    // box = gtk_hbox_new (homogeneous, spacing);
    // gtk_container_add(GTK_CONTAINER(main), box);
    // gtk_container_set_border_width(GTK_CONTAINER(box), 40);

    // gtk_box_pack_start (GTK_BOX (box1), label, FALSE, FALSE, 0);

    // gpointer data;
    // t_user *s = (t_user*)data;
    // s->user = gtk_entry_get_text(GTK_ENTRY(s->euser)); //поле ввод сообщения

    //mycode

    gtk_widget_show_all(main);
}

// static void insert_component(t_user *i) {
//     char *markup = NULL;

//     gtk_fixed_put(GTK_FIXED(i->fix), (i->backg_us_activ), 11, 0);
//     gtk_fixed_put(GTK_FIXED(i->fix), (i->backg_us_slept), 11, 0);
//     gtk_widget_set_opacity(i->but, 0.0);
//     gtk_fixed_put(GTK_FIXED(i->fix), (i->img), 23, 14);
//     gtk_fixed_put(GTK_FIXED(i->fix), (i->frame_photo_act), 23, 14);
//     gtk_fixed_put(GTK_FIXED(i->fix), (i->frame_photo_slept), 23, 14);
//     gtk_widget_set_size_request(i->but, 305, 79);
//     gtk_fixed_put(GTK_FIXED(i->fix), (i->but), 11, 0);
//     markup = g_markup_printf_escaped(MX_NAME_COLOR(i->m->style->color), i->name);
//     gtk_label_set_markup(GTK_LABEL(i->l_name), markup); 
//     reset_l_mess(i);
//     gtk_fixed_put(GTK_FIXED(i->fix), (i->l_name), 83, 21);
//     gtk_fixed_put(GTK_FIXED(i->fix), (i->l_mess), 83, 48);
//     gtk_fixed_put(GTK_FIXED(i->fix), (i->l_time), 269,  21);
//     g_free(markup);
// }



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

int main(int argc, char *argv[]) {
    t_client *client = malloc(sizeof(t_client*));
    pthread_t thread_send = 0;
    pthread_t thread_recv = 0;

    if (argc != 3)
        mx_print_error("Usage ./uchat_client %IP adress %port\n", 1, true);

    //connect to server

    mx_run_gtk((void*)client);
}


// ////"Авторизация"
// #include <gtk/gtk.h>

// #define WINDOW_AUTHOR "Авторизация"

// /* When "connect" button is clicked a message will appear */
// static void print_hello (GtkWidget *widget, gpointer data)
// {
//   g_print ("Connect button clicked\n");
// }

// int main (int argc, char *argv[]){

// /* Declare widgets */
// GtkWidget *window;
// GtkWidget *grid;
// GtkWidget *button;
// GtkWidget *button_exit;
// GtkWidget *u_name;
// //GtkWidget *h_name;
// GtkWidget *pass;
// GtkWidget *label_user;
// //GtkWidget *label_host;
// GtkWidget *label_pass;

// /*This is called in all GTK applications. Arguments are parsed from the command line and are returned to the application.*/
// gtk_init (&argc, &argv);

// /* create a new window, set its title and put it on center */
// window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
// gtk_window_set_title (GTK_WINDOW (window), WINDOW_AUTHOR);
// gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
// g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
// gtk_container_set_border_width (GTK_CONTAINER (window), 10);
// gtk_window_set_resizable(GTK_WINDOW(window), FALSE); /* window is NOT resizable */

// /* Here we construct the container that is going pack our buttons */
// grid = gtk_grid_new ();
// gtk_grid_set_row_spacing (GTK_GRID (grid), 3);

// /* Pack the container in the window */
// gtk_container_add (GTK_CONTAINER (window), grid);

// /* Add labels */
// label_user = gtk_label_new("Логин     ");
// //label_host = gtk_label_new("Hostname  ");
// label_pass = gtk_label_new("Пароль  ");

// /* Add hostname entry and label */
// //h_name = gtk_entry_new();
// //gtk_entry_set_placeholder_text (GTK_ENTRY (h_name), "Hostname"); /* imposto il testo trasparente che scompare quando clicco o scrivo */
// //gtk_grid_attach (GTK_GRID (grid), label_host, 0, 0, 1, 1);
// //gtk_grid_attach (GTK_GRID (grid), h_name, 1, 0, 1, 1);

// /* Add username entry and label */
// u_name = gtk_entry_new();
// gtk_entry_set_placeholder_text (GTK_ENTRY (u_name), "Логин");
// gtk_grid_attach (GTK_GRID (grid), label_user, 0, 1, 1, 1);
// gtk_grid_attach (GTK_GRID (grid), u_name, 1, 1, 2, 1);

// /* Add password entry and label (visibility set to 0 = not visible */
// pass = gtk_entry_new();
// gtk_entry_set_placeholder_text (GTK_ENTRY (pass), "Пароль");
// gtk_grid_attach (GTK_GRID (grid), label_pass, 0, 2, 1, 1);
// gtk_entry_set_visibility (GTK_ENTRY (pass), 0);
// gtk_grid_attach (GTK_GRID (grid), pass, 1, 2, 1, 1);

// /* Add connect button */
// button = gtk_button_new_with_label ("Вход");
// g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);  // your funct
// gtk_grid_attach (GTK_GRID (grid), button, 0, 3, 2, 1);

// /* Add quit button */
// button_exit = gtk_button_new_with_label ("Выход");
// g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);
// gtk_grid_attach (GTK_GRID (grid), button, 0, 4, 2, 1);

// /* Now that we are done packing our widgets, we show them all in one go, by calling gtk_widget_show_all() on the window.*/
// gtk_widget_show_all (window);

// /* All GTK applications must have a gtk_main(). Control ends here and waits for an event to occur (like a key press or a mouse event),
//  * until gtk_main_quit() is called. */
// gtk_main ();

// return 0;
// }



// //"REGISTRAT"-------------------------------------------------=-===-=-=-=----------------------------------------------------
// #include <gtk/gtk.h>

// #define WINDOW_REG "Регистрация"
// #define PASSS_NOT_TRUE "Пароли не совпадают. Введите заново."

// #define WRONG1 "Подтвердите пароль"
// #define WRONG2 "Заполните первое поле пароль"
// #define WRONG3 "Пароль не введен"

// /* When "connect" button is clicked a message will appear */
// static void print_hello (GtkWidget *widget, gpointer data)
// {
//   g_print ("Connect button clicked\n");
// }

// static void wrong_pass();


// int mx_strlen_for_cf(const char *s){
//     int i;
    
//     for (i = 0; s[i] != '\0'; i++);
//     return i;
// }

// static bool mx_alphabet(char c){
//     bool i = false;
    
//     if ((c > 64 && c < 91) || (c > 96 && c < 123))
//         i = true;
//     return i;
// }

// bool mx_check_form(const char *form) {
//     int count = 0;

//     if (!form)
//         return false;
//     for (int i = 0; form[i] != '\0'; i++)
//         if (!mx_alphabet(form[i]))
//             return false;
//     count = mx_strlen_for_cf(form);
//     if (count < MIN_COUNT_FORM || count > MAX_COUNT_FORM)
//         return false;
//     return true;
// }

// static void check_user_email (GtkWidget *button, gpointer gpass) {
//     t_client *c = (t_client*)gpass;
//     //GtkWidget *email_or_user_wrong;

//     c->email = gtk_entry_get_text(GTK_ENTRY(c->email)); //c->email конст чар которую могу тебе передать
//     c->login = gtk_entry_get_text(GTK_ENTRY(c->euser));

//     if(!mx_check_form(c->user))
//         g_print ("email > 5 букав)))\n");
//     else {
//         mx_client_create_request(c, 1);
//         //и открыть окно чата если ок нет то 
//     }
// }

// static void check_pass (GtkWidget *button, gpointer gpass) {
//     t_pass *p = (t_pass *)gpass;

//     GtkWidget *label_wrong;

//     p->pass = gtk_entry_get_text(GTK_ENTRY(p->epass)); 
//     p->pass2 = gtk_entry_get_text(GTK_ENTRY(p->epass2));
//     // printf("%s\n%s\n", s->pass, s->pass2);
//     // printf("%s\n%s", p->pass, p->pass2);

//     label_wrong = gtk_label_new("Пароли не совпадают. Введите заново");
    
//     if (strcmp(p->pass, p->pass2) != 0) {
//         if ((strlen(p->pass) != 0) && (strlen(p->pass2) == 0)) {
//             g_print ("Подтвердите пароль");
//             label_wrong = gtk_label_new(WRONG1);
//             wrong_pass(label_wrong);
//         }
//         if ((strlen(p->pass) == 0) && (strlen(p->pass2) != 0)) {
//             g_print ("Заполните первое поле пароль");
//             label_wrong = gtk_label_new(WRONG2);
//             wrong_pass(label_wrong);
//         }
//         if ((strcmp(p->pass, p->pass2) > 0 || strcmp(p->pass, p->pass2) < 0) && (strlen(p->pass2) != 0))
//             if (strlen(p->pass) != 0) {
//                 g_print (PASSS_NOT_TRUE);
//                 label_wrong = gtk_label_new(PASSS_NOT_TRUE);
//                 wrong_pass(label_wrong);
//         }
//     }
//     if ((strlen(p->pass) == 0) && (strlen(p->pass2) == 0)) {

//         g_print ("     Пароль не введен");
//         label_wrong = gtk_label_new(WRONG3);
//         wrong_pass(label_wrong);
//     }

// }

// static void close_wrong_pass(GtkWidget *window, GtkWidget *button, gpointer data) {

//     gtk_widget_destroy(window);
//     gtk_widget_destroy(button);
// }

// static void wrong_pass(GtkWidget *label_wrong) {
//     //отркрыть окно поверх текущего
//     GtkWidget *window;
//     GtkWidget *grid;
//     // GtkWidget *label_wrong;
//     GtkWidget *button;
//     t_pass *p;
//     t_client *s;


//     // gtk_init (&argc, &argv);

// /* create a new window, set its title and put it on center */
// window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
// gtk_window_set_title (GTK_WINDOW (window), "Ошибка");
// gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
// g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
// gtk_container_set_border_width (GTK_CONTAINER (window), 10);
// gtk_window_set_resizable(GTK_WINDOW(window), FALSE); /* window is NOT resizable */

// grid = gtk_grid_new ();
// gtk_grid_set_row_spacing (GTK_GRID (grid), 4);

// /* Pack the container in the window */
// gtk_container_add (GTK_CONTAINER (window), grid);

// /* Add labels */
// // label_wrong = gtk_label_new("Пароли не совпадают. Введите заново");
// // label_accept_pass = gtk_label_new("Пароль  ");

// /* Add hostname entry and label */
// gtk_grid_attach (GTK_GRID (grid), label_wrong, 0, 0, 1, 1);

// button = gtk_button_new_with_label ("Повторить ввод");
// g_signal_connect (button, "clicked", G_CALLBACK (close_wrong_pass), window);
// gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 2, 1);

//     gtk_widget_show_all (window);

// /* All GTK applications must have a gtk_main(). Control ends here and waits for an event to occur (like a key press or a mouse event),
//  * until gtk_main_quit() is called. */
//     gtk_main ();

// }


// int main (int argc, char *argv[]) {

// /* Declare widgets */
// gpointer data;
// void *gpass;
// GtkWidget *window;
// GtkWidget *grid;
// GtkWidget *button;
// GtkWidget *button_exit;
// GtkWidget *u_name;
// GtkWidget *label_user;
// //GtkWidget *h_name;
// GtkWidget *pass;
// GtkWidget *accept_pass;
// //GtkWidget *label_host;
// GtkWidget *label_pass;
// GtkWidget *label_accept_pass;
// GtkWidget *email;
// GtkWidget *label_email;
// t_pass *p;
// t_client *s;

// /*This is called in all GTK applications. Arguments are parsed from the command line and are returned to the application.*/
// gtk_init (&argc, &argv);

// /* create a new window, set its title and put it on center */
// window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
// gtk_window_set_title (GTK_WINDOW (window), WINDOW_REG);
// gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
// g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
// gtk_container_set_border_width (GTK_CONTAINER (window), 10);
// gtk_window_set_resizable(GTK_WINDOW(window), FALSE); /* window is NOT resizable */

// /* Here we construct the container that is going pack our buttons */
// grid = gtk_grid_new ();
// gtk_grid_set_row_spacing (GTK_GRID (grid), 4);

// /* Pack the container in the window */
// gtk_container_add (GTK_CONTAINER (window), grid);

// /* Add labels */
// label_user = gtk_label_new("Логин     ");
// label_email = gtk_label_new("Email     ");
// //label_host = gtk_label_new("Hostname  ");
// label_pass = gtk_label_new("Пароль  ");
// label_accept_pass = gtk_label_new("Пароль  ");

// /* Add hostname entry and label */
// s->euser  = gtk_entry_new();
// gtk_entry_set_placeholder_text (GTK_ENTRY (s->euser), "Логин"); /* imposto il testo trasparente che scompare quando clicco o scrivo */
// gtk_grid_attach (GTK_GRID (grid), label_user, 0, 0, 1, 1);
// gtk_grid_attach (GTK_GRID (grid), s->euser, 1, 0, 1, 1);

// /* Add username entry and label */
// s->email = gtk_entry_new();
// gtk_entry_set_placeholder_text (GTK_ENTRY (s->email), "Email");
// gtk_grid_attach (GTK_GRID (grid), label_email, 0, 1, 1, 1);
// gtk_grid_attach (GTK_GRID (grid), s->email, 1, 1, 2, 1);

// /* Add password entry and label (visibility set to 0 = not visible */
// p->epass = gtk_entry_new();
// gtk_entry_set_placeholder_text (GTK_ENTRY (p->epass), "Пароль");
// gtk_grid_attach (GTK_GRID (grid), label_pass, 0, 2, 1, 1);
// gtk_entry_set_visibility (GTK_ENTRY (p->epass), 0);
// gtk_grid_attach (GTK_GRID (grid), p->epass, 1, 2, 1, 1);

// p->epass2 = gtk_entry_new();
// gtk_entry_set_placeholder_text (GTK_ENTRY (p->epass2), "Подтвердите Пароль");
// gtk_grid_attach (GTK_GRID (grid), label_accept_pass, 0, 3, 1, 1);
// gtk_entry_set_visibility (GTK_ENTRY (p->epass2), 0);
// gtk_grid_attach (GTK_GRID (grid), p->epass2, 1, 3, 1, 1);

// /* Add connect button */
// button = gtk_button_new_with_label ("Вход");
// g_signal_connect (button, "clicked", G_CALLBACK (check_pass), p);
// g_signal_connect (button, "clicked", G_CALLBACK (check_user_email), s);
// gtk_grid_attach (GTK_GRID (grid), button, 0, 4, 2, 1);

// // }

// /* Add quit button */
// button_exit = gtk_button_new_with_label ("Выход");
// g_signal_connect (button_exit, "clicked", G_CALLBACK (gtk_main_quit), NULL);
// gtk_grid_attach (GTK_GRID (grid), button_exit, 0, 5, 2, 1);

// /* Now that we are done packing our widgets, we show them all in one go, by calling gtk_widget_show_all() on the window.*/
// gtk_widget_show_all (window);

// /* All GTK applications must have a gtk_main(). Control ends here and waits for an event to occur (like a key press or a mouse event),
//  * until gtk_main_quit() is called. */
//     gtk_main ();

//     return 0;
// }


// //main reg or author-----------------------------------------------------------------------------------------------------
// #include <gtk/gtk.h>

// #define WINDOW_REG "Главная"

// /* When "connect" button is clicked a message will appear */
// static void print_hello (GtkWidget *widget, gpointer data)
// {
//   g_print ("Connect button clicked\n");
// }

// int main (int argc, char *argv[]) {

// /* Declare widgets */
// GtkWidget *window;
// GtkWidget *grid;
// GtkWidget *button;

// /*This is called in all GTK applications. Arguments are parsed from the command line and are returned to the application.*/
// gtk_init (&argc, &argv);

// /* create a new window, set its title and put it on center */
// window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
// gtk_window_set_title (GTK_WINDOW (window), WINDOW_REG);
// gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
// g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
// gtk_container_set_border_width (GTK_CONTAINER (window), 10);
// gtk_window_set_resizable(GTK_WINDOW(window), FALSE); /* window is NOT resizable */

// /* Here we construct the container that is going pack our buttons */
// grid = gtk_grid_new ();
// gtk_grid_set_row_spacing (GTK_GRID (grid), 4);

// /* Pack the container in the window */
// gtk_container_add (GTK_CONTAINER (window), grid);

// /* Add connect button */
// button = gtk_button_new_with_label ("Авторизация");
// g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL); // your funct
// gtk_grid_attach (GTK_GRID (grid), button, 0, 0, 20, 1);

// button = gtk_button_new_with_label ("Регистрация");
// g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
// gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 20, 1);

// /* Add quit button */
// button = gtk_button_new_with_label ("Выход");
// g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);
// gtk_grid_attach (GTK_GRID (grid), button, 0, 2, 20, 1);

// /* Now that we are done packing our widgets, we show them all in one go, by calling gtk_widget_show_all() on the window.*/
// gtk_widget_show_all (window);

// /* All GTK applications must have a gtk_main(). Control ends here and waits for an event to occur (like a key press or a mouse event),
//  * until gtk_main_quit() is called. */
//     gtk_main ();

//     return 0;
// }