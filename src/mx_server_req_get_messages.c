#include "uchat.h"

void mx_server_req_get_messages(t_server *server, cJSON *root) {
    t_list_arr *res = NULL;
    char *cond = mx_strdup("WHERE room_id");
    if (!root)
        mx_print_error_json(root);
}
