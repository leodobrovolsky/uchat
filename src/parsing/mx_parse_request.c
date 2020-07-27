#include "uchat.h"

void mx_parse_request(t_server *main, cJSON *root, int time_int) {
    if (!root)
        mx_print_error_json(root);
    if (root->valueint == REQ_CONNECT)
        mx_server_req_connect(main);
    else if (root->valueint == REQ_AUTORIZATION)
        mx_server_req_autorization(main, root->next);
    else if (root->valueint == REQ_GET_MESSAGES)
        mx_server_req_get_messages(main, root->next);
}
