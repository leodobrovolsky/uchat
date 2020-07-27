#include "uchat.h"

void mx_print_user_create(t_user_create *user) {
    mx_printstr("Логин: ");
    mx_printstr(user->login);
    mx_printstr("\nПароль: ");
    mx_printstr(user->password);
    mx_printstr("\nИмя: ");
    mx_printstr(user->name);
    mx_printstr("\nФамилия: ");
    mx_printstr(user->surname);
    mx_printstr("\nEmail: ");
    mx_printstr(user->email);
}
