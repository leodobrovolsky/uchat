#include "uchat.h"

void mx_parse_com(char *str) {

    if (!mx_strcmp(str, SERVER_COM_HELP))
        mx_run_help();
    else if (!mx_strcmp(str, SERVER_COM_CREATE_MANAGER))
        mx_server_create_manager();
    else if (!mx_strcmp(str, SERVER_COM_MANAGERS))
        mx_server_managers();
    else if (!mx_strcmp(str, SERVER_COM_EXIT))
        exit(0);
    else if (!mx_strcmp(str, SERVER_COM_DELETE_MANAGER))
        mx_server_delete_manager();
    else if (!mx_strcmp(str, SERVER_COM_EDIT_MANAGER))
        mx_server_edit_manager();
    else if (!mx_strcmp(str, SERVER_COM_SELECT))
        mx_server_select();
}
