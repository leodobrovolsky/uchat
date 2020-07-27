#include "uchat.h"

static void mx_server_add_active_user(int fd, char *user_id) {
    t_database db;
    char **data = mx_create_char_arr(TABLE_ACTIVE_USERS_COLUMNS);

    data[0] = mx_strdup("NULL");
    data[1] = mx_strdup(user_id);
    data[2] = mx_strdup(mx_itoa(fd));
    db.name_db = DATABASE_NAME;
    db.name_table = TABLE_NAME_ACTIVE_USERS;
    db.table = mx_create_t_table_active_users();
    mx_push_data_table(&db.table, data);
    mx_insert_data(db);
    mx_free_t_table(&db.table);
    mx_del_strarr(&data);
}

void mx_server_req_autorization(t_server *server, cJSON *root) {
    t_list_arr *res = NULL;

    if(!root || !(root->next))
        mx_print_error_json(root);
    res = mx_server_search_user(root->valuestring, root->next->valuestring);
    if (res)
        server->user = mx_arr_to_user_create(res->data);
    else {
    	mx_server_add_active_user(server->client_fd, res->data[0]);
        server->exit_status = true;
    }
}
