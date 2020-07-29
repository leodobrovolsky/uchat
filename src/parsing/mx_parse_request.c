#include "uchat.h"

void mx_server_req_register(t_server *s, cJSON *root) {
    t_list_arr *res = NULL;
    char *str = mx_strdup("WHERE login = '");
    t_database db;
    char **data = mx_create_char_arr(TABLE_USERS_COLUMNS);
    //char *str = mx_autorization_response_to_json();
    
    if(!root || !(root->next))
        mx_print_error_json(root);
    mx_stradd(&str, root->valuestring);
    mx_stradd(&str, "'");
    res = mx_get_select(TABLE_NAME_USERS, str);
    if (res) {
    	mx_strdel(&str);
    	str = mx_register_response_to_json(RESPONSE_REGISTER_FAIL);
    	mx_server_send(s->cfd, str);
    }
    else {
    	mx_strdel(&str);
    	str = mx_register_response_to_json(RESPONSE_REGISTER_OK);
        db.name_db = DATABASE_NAME;
        db.name_table = TABLE_NAME_USERS;
        db.table = mx_create_t_table_users();
        data[0] = mx_strdup("NULL");
        data[1] = mx_strdup(root->valuestring);
        data[2] = mx_strdup(root->next->valuestring);
        data[3] = mx_strdup(root->next->next->valuestring);
        data[4] = mx_strdup(root->next->next->next->valuestring);
        data[5] = mx_strdup(root->next->next->next->next->valuestring);
        data[6] = mx_strdup(USER_TYPE_USUAL);
        data[7] = mx_strdup(USER_STATUS_ACTIVE);
        mx_push_data_table(&db.table, data);
        mx_insert_data(db);
        mx_server_send(s->cfd, str);
        mx_free_t_table(&db.table);
        mx_del_strarr(&data);
        mx_free_arr_list(&res);
        mx_strdel(&str);
    }
}

void mx_server_req_edit_user(t_server *s, cJSON *root) {
    t_list_arr *res = NULL;
    char *str = mx_strdup("WHERE login = '");
    t_database db;
    char **data = mx_create_char_arr(TABLE_USERS_COLUMNS);
    //char *str = mx_autorization_response_to_json();

    if(!root || !(root->next))
        mx_print_error_json(root);
    mx_stradd(&str, root->valuestring);
    mx_stradd(&str, "'");
    res = mx_get_select(TABLE_NAME_USERS, str);
    if (res) {
    	mx_strdel(&str);
    	str = mx_edit_user_response_to_json(RESPONSE_REGISTER_FAIL);
    	mx_server_send(s->cfd, str);
    }
    else {
    	str = mx_edit_user_response_to_json(RESPONSE_REGISTER_OK);
        db.name_db = DATABASE_NAME;
        db.name_table = TABLE_NAME_USERS;
        db.table = mx_create_t_table_users();
        data[0] = mx_strdup("NULL");
        data[1] = mx_strdup(root->valuestring);
        data[2] = mx_strdup(root->next->valuestring);
        data[3] = mx_strdup(root->next->next->valuestring);
        data[4] = mx_strdup(root->next->next->next->valuestring);
        data[5] = mx_strdup(root->next->next->next->next->valuestring);
        data[6] = mx_strdup(USER_TYPE_USUAL);
        data[7] = mx_strdup(USER_STATUS_ACTIVE);
        mx_push_data_table(&db.table, data);
        mx_update_data(db, str);
        mx_server_send(s->cfd, str);
        mx_free_t_table(&db.table);
        mx_del_strarr(&data);
        mx_free_arr_list(&res);
        mx_strdel(&str);
    }
}

void mx_parse_request(t_server *main, cJSON *root, int time_int) {

    if (!root)
        mx_print_error_json(root);
    if (root->valueint == REQ_CONNECT)
        mx_server_req_connect(main);
    else if (root->valueint == REQ_AUTORIZATION)
        mx_server_req_autorization(main, root->next);
    else if (root->valueint == REQ_GET_MESSAGES)
        mx_server_req_get_messages(main, root->next);
    else if (root->valueint == REQ_REGISTER)
    	mx_server_req_register(main, root->next);
    else if (root->valueint == REQ_EDIT_USER)
    	mx_server_req_edit_user(main, root->next);
}
