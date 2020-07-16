#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include "libmx.h"
#include "cJSON.h"
#include "sqlite3.h"

#define SEND_BUFF_SIZE 1025
#define SERVER_IP_ADDRESS "localhost"
#define SERVER_PORT 5000
#define MAX_CLIENTS 10

typedef struct s_server {
    int listenfd;
    int confd;
    struct sockaddr_in serv_addr;
    char *send_buff;
} t_server;
