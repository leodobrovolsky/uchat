#include "uchat.h"

void mx_server_send(int fd, char *str) {
    send(fd, str, BUFFER_SIZE, 0);
}
