#include "server.h"

int main() {
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;
    char recvBuff[1024];
    char sendBuff[1025];
    time_t ticks;
    int n = 0;

    listenfd = socket(AF_INET, SOCK_STREAM, 0); // AF_INET - ipv4, SOCK_STREAM - TCP protocol
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(listenfd, 10);

    while(1) {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        ticks = time(NULL);
        snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
        write(connfd, sendBuff, strlen(sendBuff));
        while ( (n = read(connfd, recvBuff, sizeof(recvBuff)-1)) > 0)
        {
            recvBuff[n] = 0;
            if(fputs(recvBuff, stdout) == EOF)
            {
                printf("\n Error : Fputs error\n");
            }
        }             
        close(connfd);
        sleep(1);
    }
}

// t_server *mx_create_server_struct() {
//     t_server *server = (t_server*)malloc(sizeof(t_server));

//     server->listenfd = 0;
//     server->confd = 0;
//     server->send_buff = mx_strnew(SEND_BUFF_SIZE);
//     server->serv_addr.sin_family = AF_INET;
//     server->serv_addr.sin_addr.s_addr = htons(INADDR_ANY);
//     server->serv_addr.sin_port = htons(SERVER_PORT);
//     return server;
// }


// void mx_server_loop(t_server *serv) {
//     int ticks = 0;

//     while(1) {
//         serv->connfd = accept(serv->listenfd, (struct sockaddr*)NULL, NULL);
//         ticks = time(NULL);
//     }
// }


// int main () {
//     t_server *s = mx_create_server_struct();
    
//     s->listenfd = socket(AF_INET, SOCK_STREAM, 0);
//     if (s->listenfd == -1)
//         exit(1);
//     bind(s->listenfd, (struct sockaddr*)&s->serv_addr, sizeof(s->serv_addr));
//     listen(s->listenfd, MAX_CLIENTS);
//     mx_server_loop(s);
// }
