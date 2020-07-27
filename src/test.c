#include "uchat.h"

void mx_print_json_struct(cJSON *root) {
    mx_printstr("type: ");
    mx_printint(root->type);
    mx_printstr("\nvaluestring: ");
    if (root->valuestring)
        mx_printstr(root->valuestring);
    else
        mx_printstr("null");
    mx_printstr("\nvalueint: ");
    mx_printint(root->valueint);
    mx_printstr("\nstring: ");
    if(root->string)
        mx_printstr(root->string);
    else
        mx_printstr("null");
    mx_printchar('\n');
}



void mx_print_error_json(cJSON *root) {
    if(PRINT_JSON_ERROR) {
        if (EXIT_PRINT_ERROR) {
            print_preallocated(root);
            exit(1);
        }
        else
            print_preallocated(root);
    }
}

void mx_server_req_connect(t_server *main) {
    main = NULL;
    mx_printstr("RESPONSE_CONNECT OK\n");
    //add code
}

bool mx_server_search_user(char *login, char *password) {
    t_list_arr *res = NULL;
    t_database db;
    char *cond = mx_strdup("WHERE login = '");

    db.name_db = DATABASE_NAME;
    db.name_table = TABLE_NAME_USERS;
    db.table = mx_create_t_table_users();
    mx_stradd(&cond, login);
    mx_stradd(&cond, "' AND password = '");
    mx_stradd(&cond, password);
    mx_stradd(&cond, "' AND status = '");
    mx_stradd(&cond, USER_STATUS_ACTIVE);
    mx_stradd(&cond, "'");
    res = mx_select_data(db, cond, TABLE_USERS_COLUMNS);
    if (!res) {
        mx_free_t_table(&db.table);
        mx_strdel(&cond);
        return false;
    }
    else {

        mx_free_t_table(&db.table);
        mx_strdel(&cond);
        return true;       
    }
}

void mx_server_req_autorization(t_server *server) {
    bool check = false;

    if(!root || !(root->next))
        mx_print_error_json(root);
    check = 
    server->user->login = mx_strdup(root->valuestring);
    server->user->password = mx_strdup(root->next->valuestring);
}

void mx_parse_request(t_server *main, cJSON *root, int time_int) {
    if (!root)
        mx_print_error_json(root);
    if (root->valueint == REQ_CONNECT)
        mx_server_req_connect(main);
    else if (root->valueint == REQ_AUTORIZATION)
        mx_server_req_autorization(main, root->next);
}

void mx_parse_response(t_server *main, cJSON *root, int time_int) {
    
    mx_printstr("OK");
    main = NULL;
    root = NULL;
    time_int = 0;
}

void mx_parse_json(t_server *main, char *str) {
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

int main() {
    t_server *s = malloc(sizeof(t_server));
    //char *res = mx_connect_request_to_json();
    //char *res = mx_connect_response_to_json(1);
    char *res = mx_autorization_request_to_json("ldobrovols", "123");
    //char *res = mx_autorization_response_to_json(12);
    t_user_create user;
    user.login = "ldobrovols";
    user.password = "123";
    user.name = "Leonid";
    user.surname = "Dobrovolsky";
    user.email = "leo@mail.com";
    user.status = "active";
    user.rules = "admin";
    

    // char *mes1[3] = {"123", "Leonid","hello"};
    // char *mes2[3] = {"1243", "MAX", "hy"};
    t_list_arr *mes = NULL;
    char **mes1 = mx_create_char_arr(3);
    char **mes2 = mx_create_char_arr(3);
    mes1[0] = mx_strdup("123");
    mes1[1] = mx_strdup("Leonid");
    mes1[2] = mx_strdup("hello");
    mes2[0] = mx_strdup("1234");
    mes2[1] = mx_strdup("MAX");
    mes2[2] = mx_strdup("hy");


    mx_arr_push_back(&mes, mes1);
    mx_arr_push_back(&mes, mes2);

    //char *res = mx_register_request_to_json(user);
    //char *res = mx_register_response_to_json(-1);
    //char *res = mx_edit_user_request_to_json(user);
    //char *res = mx_edit_user_response_to_json(1);
    //char *res = mx_get_messages_request_to_json("forum");
    //char *res = mx_get_messages_response_to_json(mes, "forum", 0);
    //char *res = mx_get_rooms_request_to_json("leonid");
    //char *res = mx_get_rooms_response_to_json(mes1, 0);
    //char *res = mx_get_users_in_rooms_request_to_json("forum", "1");
    //char *res = mx_get_users_in_rooms_response_to_json("forum", mes1, 0);
    //char *res = mx_leav_room_request_to_json("forum", "igor");
    //char *res= mx_leav_room_response_to_json(0);
    //char *res = mx_add_user_to_room_request("forum", "igor");
    //char *res = mx_add_user_to_room_response(1);
    //char *res = mx_load_profile_request("leonid");
    //char *res = mx_load_profile_response_to_json(user, 12);
    //char *res = mx_create_room_request_to_json("asldf");
    //char *res = mx_create_room_response_to_json(1);

    //cJSON *root = NULL;

    
    mx_printstr(res);
    mx_parse_json(s, res);
    //mx_strdel(&res);
    // root = cJSON_Parse(res);
    // if (print_preallocated(root) != 0) {
    //     cJSON_Delete(root);
    //     exit(EXIT_FAILURE);
    // }
    // cJSON_Delete(root);
}
