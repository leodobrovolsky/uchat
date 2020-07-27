#include "uchat.h"

char *mx_valid_input_password() {
    char *passwd1 = mx_strnew(SERVER_INPUT_SIZE);
    char *passwd2 = mx_strnew(SERVER_INPUT_SIZE);
    int res = 0;

    mx_printstr("Введите пароль-> ");
    mx_getch(passwd1);
    mx_printstr("Введите пароль еще раз-> ");
    mx_getch(passwd2); 
    res = mx_strcmp(passwd1, passwd2);
    mx_strdel(&passwd2);
    if (!res)
        return passwd1;
    else {
        mx_printstr("Пароли не совпадают! Попробуйте еще раз\n");
        mx_strdel(&passwd1);
        return NULL;
    }
}
