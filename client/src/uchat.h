#ifndef UCHAT_H
#define UCHAT_H

#include <gtk/gtk.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
//#include "./libxml2/inc/libmx.h"

// typedef struct s_data {
//     int number; //кол-во подключенных пользователей
//     struct user;
// }   t_data;

// typedef struct user {
//     char *login;
//     char *password;
//     char *email;
// }   user;
 typedef struct s_user {
    GtkApplication *app;
    GtkWidget *euser, *epass, *epass2, *email, *sex1, *entry1, *entry2;
    GtkWidget *ap_entry1, *ap_entry2;
    GtkWidget *a_label4, *a_label6;
    GtkWidget *chat_label1;
    GtkWidget *chat_entry;
    GtkWidget *main_window, *e_window, *reg_window, *reg_right_wind, *a_window, *ap_window, *chat_window;
    const char *user ;
    const char *pass ;
    const char *pass2 ;
    const char *email1 ;
    const char *sex;
    char *cjson;
    int fl;
    const char *name;
    const char *surname;
    const char *current;
    int deth;
}   t_user;


void mx_headband(GtkApplication* app, gpointer data);
void mx_register(GtkApplication* app, gpointer data);
bool mx_valid(const char *s, int n);
void mx_account(gpointer data);
void mx_enter(GtkApplication* app, gpointer data);
void mx_chat_main(GtkApplication* app, gpointer data);
//libmx
int mx_strcmp(const char *s1, const char *s2);
bool mx_isdigit(int c);
bool mx_isalpha(int c);
int mx_strlen(const char *s);


#endif
