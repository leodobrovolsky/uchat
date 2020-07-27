#include "uchat.h"

void mx_server_req_get_messages(t_server *server, cJSON *root) {
    t_list_arr *res = NULL;

    if (!root)
        mx_print_error_json(root);
    res = mx_server_get_mes_list(root->valuestring);
}
