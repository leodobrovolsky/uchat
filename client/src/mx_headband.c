#include "uchat.h"

// static void print_hello (GtkWidget *widget, gpointer   data) {
//   g_print ("Hello World\n");
// }

void mx_headband(GtkApplication* app, gpointer data) {
    //GtkWidget *window;
    GtkWidget *button1, *button2;
    GtkWidget *button_box, *box;
    GtkWidget *image1, *image2;
    t_user *s = (t_user*)data;

    //GtkColorChooser *chooser = NULL;
    //GdkRGBA color = {0.0, 0.0, 0.0, 0.0};

    s->main_window = gtk_application_window_new(app);
    gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(s->main_window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(s->main_window), "UCHAT");
    gtk_window_set_default_size(GTK_WINDOW(s->main_window), 700, 1000);
GtkStyleContext *context;
context = gtk_widget_get_style_context(s->main_window);
gtk_style_context_add_class(context,".window_main");
    /* color->red = 0.0;
     color->green = 0.0;
     color->blue = 0.0;*/
GdkDisplay *display;
GdkScreen *screen;
display = gdk_display_get_default ();
screen = gdk_display_get_default_screen (display);

GtkCssProvider *provider;

provider = gtk_css_provider_new ();

gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

gtk_css_provider_load_from_path(GTK_CSS_PROVIDER(provider),"styles.css",NULL);
gtk_css_provider_load_from_data(provider, "GtkButton { background: green; }", -1, NULL);     

/*    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                   GTK_STYLE_PROVIDER(provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_USER);*/

   // g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
   // gtk_container_add(GTK_CONTAINER(window), label);
   // gtk_widget_show_all(window);

    //gtk_color_chooser_set_rgba(Gtk_Color_Chooser(window), &color); //ТУТ ОШИБКА!!!
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    button_box = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
    gtk_box_set_spacing(GTK_BOX(button_box), 10);
    gtk_container_add(GTK_CONTAINER(s->main_window), box);
    gtk_container_set_border_width(GTK_CONTAINER(s->main_window), 20);
    button1 = gtk_button_new_with_label ("Зарегистрироваться");
    button2 = gtk_button_new_with_label ("Войти");
    image1 = gtk_image_new_from_file("image2.jpg");
    image2 = gtk_image_new_from_file("sprosi.jpg");
    g_signal_connect(button1, "clicked", G_CALLBACK(mx_register), s);
    g_signal_connect(button2, "clicked", G_CALLBACK(mx_enter), s);
    //g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    gtk_container_add(GTK_CONTAINER(box), image1);
    gtk_container_add(GTK_CONTAINER(box), image2);
    gtk_container_add(GTK_CONTAINER(button_box), button1);
    gtk_container_add(GTK_CONTAINER(button_box), button2);
    gtk_container_add(GTK_CONTAINER(box), button_box);
    gtk_widget_show_all(s->main_window);
  }

//СДЕЛАТЬ ЕЩЕ ТУТ 
//1 Добить цвет строка 21
//2 Сделат кнопку смены цвета
//3 Масштабировать картинки
//4 Аудитор
//5 сделать функцию закрытия окна