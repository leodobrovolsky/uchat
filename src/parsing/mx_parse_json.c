#include "uchat.h"

void mx_server_parse_json(t_server *main, char *str) {
    cJSON *root = cJSON_Parse(str);
    
    if (!root || !root->child)
        mx_print_error_json(root);
    root = root->child;
    if (!root)
        mx_print_error_json(root);
    root = root->next;
    if (!root)
        mx_print_error_json(root);
    if (!mx_strcmp(root->valuestring, JSON_TYPE_REQUEST))
        mx_parse_request(main, root->next, root->prev->valueint);
    else if (!mx_strcmp(root->valuestring, JSON_TYPE_RESPONSE))
        mx_parse_response(main, root->next, root->prev->valueint);
    else
        mx_print_error_json(root);
    cJSON_Delete(root);
}
