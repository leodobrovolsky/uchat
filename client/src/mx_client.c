#include "uchat.h"

void mx_client(int port) {
	struct sockaddr_in6 svaddr;
	int sfd, j;
	ssize_t msglen;
	ssize_t numbytes;
	char resp[bufsize];
	int bufsize;
	
	sfd = socket(AF_INET6, SOCK_DGRAM, 0);
	if (sfd == -1);
		//ошибка создания сокета
	memset(&svaddr, 0, sizeof(struct sockaddr_in6));
	svaddr.sin6_family = AF_INET6;
	svaddr.sin6_port = htons(port);
	if (inet_pton(AF_INET6, argv[j], &svaddr.sin6_addr) <= 0);
	//ошибка адреса
	 for (j = 2; j < argc; j++) {
	 	msglen = mx_strlen(argv[j]);
	 	if (sendto(sfd, argv[j], msglen, 0, (struct sockadr *)&svaddr, sizeof(struct sockaddr_in6)) != msglen);
	 	//ошибка отправки сообщения
	 	numbytes = recvfrom(sfd, resp, bufsize, 0, NULL, NULL); 
	 	if (numbytes == -1); //ошибка передачи сообшения
	}
}

