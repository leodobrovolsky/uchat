#include "../inc/client.h"

// int main(int argc, char *argv[]) {
//     int sockfd = 0, n = 0;
//     char recvBuff[1024];
//     struct sockaddr_in serv_addr;

//     if(argc != 2) {
//         printf("\n Usage: %s <ip of server> \n",argv[0]);
//         return 1;
//     }
//     memset(recvBuff, '0',sizeof(recvBuff));
//     if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
//     {
//         printf("\n Error : Could not create socket \n");
//         return 1;
//     }
//     memset(&serv_addr, '0', sizeof(serv_addr));
//     serv_addr.sin_family = AF_INET;
//     serv_addr.sin_port = htons(5000);
//     if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
//     {
//         printf("\n inet_pton error occured\n");
//         return 1;
//     }
//     if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
//     {
//        printf("\n Error : Connect Failed \n");
//        return 1;
//     }
//     while ( (n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
//     {
//         recvBuff[n] = 0;
//         if(fputs(recvBuff, stdout) == EOF)
//         {
//             printf("\n Error : Fputs error\n");
//         }
//     }
//     if(n < 0)
//     {
//         printf("\n Read error \n");
//     }
//     return 0;
// }


t_client *mx_create_client_struct(const char *IP) {
    t_client *client = (t_client*)malloc(sizeof(t_client));
    int in_st = 0;

    client->sockfd = 0;
    client->serv_addr.sin_family = AF_INET;
    client->serv_addr.sin_addr.s_addr = htons(INADDR_ANY);
    client->serv_addr.sin_port = htons(SERVER_PORT); 
    in_st = inet_pton(AF_INET, IP, &client->serv_addr.sin_addr);
    if(in_st <= 0)
        mx_print_error("\n inet_pton error occured\n", 1);

    return client;
}

void mx_client_loop(t_server *serv) {
    int ticks = 0;

    while(1) {
        serv->connfd = accept(serv->listenfd, (struct sockaddr*)NULL, NULL);
        ticks = time(NULL);
    }
}


int main (int argc, char *argv[]) {
    t_client *c = NULL;
    int confd = 0;
    
    if(argc != 2) {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    }
    c = mx_create_client_struct(argv[1]);
    c->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (c->listenfd == -1)
        mx_print_error("\n error create socket\n", 1);
    confd = connect(sockfd, (struct sockaddr *)&c->serv_addr, sizeof(c->serv_addr));
    if (confd < 0)
        mx_print_error("\n error create socket\n", 1);
    mx_server_loop(c);
}
