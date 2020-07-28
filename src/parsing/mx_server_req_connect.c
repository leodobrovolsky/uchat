#include "uchat.h"

void mx_server_req_connect(t_server *main) {
    char *str = mx_connect_response_to_json(0);
    
    mx_server_send(main->sock_fd, str);
    mx_strdel(&str);
}
