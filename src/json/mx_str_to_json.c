#include "libmx.h"
#include "cJSON.h"
#include <time.h>
#include "uchat.h"




char *mx_get_current_time() {
    int times = time(NULL);

    return mx_itoa(times);
}

char *mx_connect_request_to_json() {
    char *tmp = mx_file_to_str(CONNECT_REQUEST_FILE);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&time", times); 
    mx_strdel(&times);
    return tmp;
}

char *mx_connect_response_to_json(int status) {
    char *tmp = mx_file_to_str(CONNECT_RESPONSE_FILE);
    char *times = mx_get_current_time();
    char *st = mx_itoa(status);

    mx_replace_str(&tmp, "&time", times);
    mx_replace_str(&tmp, "&status", st); 
    mx_strdel(&times);
    mx_strdel(&st);
    return tmp;   
}

char *mx_autorization_request_to_json(char *login, char *passwd) {
    char *tmp = mx_file_to_str(AUTORIZATION_REQUEST_FILE);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&time", times);
    mx_replace_str(&tmp, "&login", login);
    mx_replace_str(&tmp, "&password", passwd);
    mx_strdel(&times);
    return tmp;
}

char *mx_autorization_response_to_json(int status) {
    char *tmp = mx_file_to_str(AUTORIZATION_RESPONSE_FILE);
    char *times = mx_get_current_time();
    char *st = mx_itoa(status);

    mx_replace_str(&tmp, "&status", st);
    mx_replace_str(&tmp, "&time", times);
    mx_strdel(&times);
    mx_strdel(&st);
    return tmp;
}

char *mx_register_request_to_json(t_user_create user) {
    char *tmp = mx_file_to_str(REGISTER_REQUEST_FILE);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&time", times);
    mx_replace_str(&tmp, "&login", user.login);
    mx_replace_str(&tmp, "&password", user.password);
    mx_replace_str(&tmp, "&name", user.name);
    mx_replace_str(&tmp, "&surname", user.surname);
    mx_replace_str(&tmp, "&email", user.email);
    mx_strdel(&times);
    return tmp;
}

char *mx_register_response_to_json(int status) {
    char *tmp = mx_file_to_str(REGISTER_RESPONSE_FILE);
    char *st = mx_itoa(status);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&time", times);
    mx_replace_str(&tmp, "&status", st);
    mx_strdel(&times);
    mx_strdel(&st);
    return tmp;
}

char *mx_edit_user_request_to_json(t_user_create user) {
    char *tmp = mx_file_to_str(EDIT_USER_REQUEST_FILE);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&time", times);
    mx_replace_str(&tmp, "&login", user.login);
    mx_replace_str(&tmp, "&password", user.password);
    mx_replace_str(&tmp, "&name", user.name);
    mx_replace_str(&tmp, "&surname", user.surname);
    mx_replace_str(&tmp, "&email", user.email);
    mx_replace_str(&tmp, "&status", user.status);
    mx_strdel(&times);
    return tmp;
}

char *mx_edit_user_response_to_json(int status) {
    char *tmp = mx_file_to_str(EDIT_USER_RESPONSE_FILE);
    char *st = mx_itoa(status);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&time", times);
    mx_replace_str(&tmp, "&status", st);
    mx_strdel(&times);
    mx_strdel(&st);
    return tmp;   
}

char *mx_get_messages_request_to_json(char *room) {
    char *tmp = mx_file_to_str(GET_MESSAGES_REQUEST_FILE);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&time", times);
    mx_replace_str(&tmp, "&room", room);
    mx_strdel(&times);
    return tmp;
}

static void mx_get_mes2(char **tmp_mes, t_list_arr *mes) {
    *tmp_mes = mx_file_to_str(MESSAGE_FILE);
    mx_replace_str(tmp_mes, "&time", mes->data[0]);
    mx_replace_str(tmp_mes, "&user", mes->data[1]);
    mx_replace_str(tmp_mes, "&text", mes->data[2]);   
}

char *mx_get_messages_response_to_json(t_list_arr *mes, char *r, int status) {
    char *tmp = mx_file_to_str(GET_MESSAGES_RESPONSE_FILE);
    char *times = mx_get_current_time();
    char *st = mx_itoa(status);
    char *tmp_mes = NULL;

    mx_replace_str(&tmp, "&id", times);
    mx_replace_str(&tmp, "&status", st);
    mx_replace_str(&tmp, "&room", r);
    while(mes) {
        mx_get_mes2(&tmp_mes, mes);
        mx_stradd(&tmp, tmp_mes);
        if (mes->next)
            mx_stradd(&tmp, ",");
        mes = mes->next;
        mx_strdel(&tmp_mes);
    }
    mx_stradd(&tmp, "]}");
    mx_strdel(&times);
    mx_strdel(&st);
    return tmp;
}

char *mx_get_rooms_request_to_json(char *user) {
    char *tmp = mx_file_to_str(GET_ROOMS_REQUEST_FILE);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&time", times);
    mx_replace_str(&tmp, "&user", user);
    mx_strdel(&times);
    return tmp;
}

char *mx_get_rooms_response_to_json(char **rooms, int status) {
    char *tmp = mx_file_to_str(GET_ROOMS_RESPONSE_FILE);
    char *st = mx_itoa(status);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&id", times);
    mx_replace_str(&tmp, "&status", st);
    for (int i = 0; rooms[i]; i++) {
        mx_stradd(&tmp, "\"");
        mx_stradd(&tmp, rooms[i]);
        mx_stradd(&tmp, "\"");
        if (rooms[i+1])
            mx_stradd(&tmp, ", ");
    }
    mx_stradd(&tmp, "]}");
    mx_strdel(&times);
    mx_strdel(&st);
    return tmp;
}

char *mx_get_users_in_rooms_request_to_json(char *room, char *user) {
    char *tmp = mx_file_to_str(GET_USERS_IN_ROOMS_REQUEST_FILE);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&time", times);
    mx_replace_str(&tmp, "&user", user);
    mx_replace_str(&tmp, "&room", room);
    mx_strdel(&times);
    return tmp;
}

char *mx_get_users_in_rooms_response_to_json(char *room, char **users, int status) {
    char *tmp = mx_file_to_str(GET_USERS_IN_ROOMS_RESPONSE_FILE);
    char *st = mx_itoa(status);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&time", times);
    mx_replace_str(&tmp, "&status", st);
    mx_replace_str(&tmp, "&room", room);
    for (int i = 0; users[i]; i++) {
        mx_stradd(&tmp, "\"");
        mx_stradd(&tmp, users[i]);
        mx_stradd(&tmp, "\"");
        if (users[i+1])
            mx_stradd(&tmp, ",");
    }
    mx_stradd(&tmp, "]}");
    mx_strdel(&times);
    mx_strdel(&st);
    return tmp;
}

char *mx_leav_room_request_to_json(char *room, char *user) {
    char *tmp = mx_file_to_str(LEAV_ROOM_REQUEST_FILE);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&room", room);
    mx_replace_str(&tmp, "&user", user);
    mx_replace_str(&tmp, "&time", times);
    mx_strdel(&times);
    return tmp;
}

char *mx_leav_room_response_to_json(int status) {
    char *tmp = mx_file_to_str(LEAV_ROOM_RESPONSE_FILE);
    char *st = mx_itoa(status);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&id", times);
    mx_replace_str(&tmp, "&status", st);
    mx_strdel(&times);
    mx_strdel(&st);
    return tmp;    
}

char *mx_add_user_to_room_request_to_json(char *user, char *room) {
    char *tmp = mx_file_to_str(ADD_USER_TO_ROOM_REQUEST_FILE);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&room", room);
    mx_replace_str(&tmp, "&user", user);
    mx_replace_str(&tmp, "&time", times);
    mx_strdel(&times);
    return tmp;   
}

char *mx_add_user_to_room_response_to_json(int status) {
    char *tmp = mx_file_to_str(ADD_USER_TO_ROOM_RESPONSE_FILE);
    char *st = mx_itoa(status);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&time", times);
    mx_replace_str(&tmp, "&status", st);
    mx_strdel(&times);
    mx_strdel(&st);
    return tmp;   
}

char *mx_load_profile_request_to_json(char *user) {
    char *tmp = mx_file_to_str(LOAD_PROFILE_REQUEST_FILE);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&time", times);
    mx_replace_str(&tmp, "&user", user);
    mx_strdel(&times);
    return tmp;
}

char *mx_load_profile_response_to_json(t_user_create user, int status) {
    char *tmp = mx_file_to_str(LOAD_PROFILE_RESPONSE_FILE);
    char *st = mx_itoa(status);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&time", times);
    mx_replace_str(&tmp, "&status", st);
    mx_replace_str(&tmp, "&login", user.login);
    mx_replace_str(&tmp, "&name", user.name);
    mx_replace_str(&tmp, "&surname", user.surname);
    mx_replace_str(&tmp, "&email", user.email);
    mx_replace_str(&tmp, "&rules", user.rules);
    mx_replace_str(&tmp, "&user_status", user.status);
    mx_strdel(&times);
    mx_strdel(&st);
    return tmp;     
}

char *mx_create_room_request_to_json(char *name) {
    char *tmp = mx_file_to_str(CREATE_ROOM_REQUEST_FILE);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&time", times);
    mx_replace_str(&tmp, "&name", name);
    mx_strdel(&times);
    return tmp;
}

char *mx_create_room_response_to_json(int status) {
    char *tmp = mx_file_to_str(CREATE_ROOM_RESPONSE_FILE);
    char *st = mx_itoa(status);
    char *times = mx_get_current_time();

    mx_replace_str(&tmp, "&time", times);
    mx_replace_str(&tmp, "&status", st);
    mx_strdel(&times);
    mx_strdel(&st);
    return tmp;     
}

int main(int argc, char *argv[]) {
    //char *res = mx_connect_request_to_json();
    //char *res = mx_connect_response_to_json(1);
    //char *res = mx_autorization_request_to_json("ldobrovols", "123");
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
    char *res = mx_create_room_response_to_json(1);

    cJSON *root = NULL;

    
    mx_printstr(res);
    //mx_strdel(&res);
    root = cJSON_Parse(res);
    if (print_preallocated(root) != 0) {
        cJSON_Delete(root);
        exit(EXIT_FAILURE);
    }
    cJSON_Delete(root);
    system("leaks -q a.out");
}
