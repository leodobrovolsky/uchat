#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include "libmx.h"

#define SEND_BUFF_SIZE 1025
#define SERVER_PORT 5000

typedef struct s_client {
    int sockld;
    struct sockaddr_in serv_addr;
} t_client;