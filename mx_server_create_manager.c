#include "uchat.h"

void mx_server_create_manager() {
    t_user_create *user = malloc(sizeof(t_user_create));
    char *check = mx_strnew(SERVER_INPUT_SIZE);
    bool insert_res = false;

    mx_printstr("Введите логин-> ");
    user->login = mx_strnew(SERVER_INPUT_SIZE);
    mx_getch(user->login);
    user->password = mx_valid_input_password();
    if (!user->password)
        return;
    mx_printstr("Введите имя-> ");
    user->name = mx_strnew(SERVER_INPUT_SIZE);
    mx_getch(user->name);
    mx_printstr("Введите фамилию-> ");
    user->surname = mx_strnew(SERVER_INPUT_SIZE);
    mx_getch(user->surname);
    mx_printstr("Введите email-> ");
    user->email = mx_strnew(SERVER_INPUT_SIZE);
    mx_getch(user->email);
    user->rules = mx_strdup("manager");
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
    mx_printstr("\nСохранить y/n ? ");
    mx_getch(check);
    if (!mx_strcmp(check, "y")) {
        insert_res = mx_insert_user(user);
        if(insert_res)
            mx_printstr("Менеджер добавлен!\n");
        else
            mx_printstr("Ошибка добавления менеджера\n");
    }
    else
        mx_printstr("Отмена добавления\n");
}
