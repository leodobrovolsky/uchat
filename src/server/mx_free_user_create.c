#include "uchat.h"

void mx_free_user_create(t_user_create **user) {
    t_user_create *tmp = *user;

    mx_strdel(&tmp->id);
    mx_strdel(&tmp->login);
    mx_strdel(&tmp->password);
    mx_strdel(&tmp->name);
    mx_strdel(&tmp->surname);
    mx_strdel(&tmp->email);
    mx_strdel(&tmp->rules);
    mx_strdel(&tmp->status);
    free(tmp);
    tmp = NULL;
}
