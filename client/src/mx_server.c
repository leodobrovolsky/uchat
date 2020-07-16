#include "uchat.h"

void mx_server(int port) {
	struct sockaddr_in6 svaddr, claddr;
	int sfd, j;
	ssize_t numbytes;
	socklen_t len;
	char buf[bufsize];
	char claddrStr[inet6_addrstrlen];
	int bufsize;
	inet6_addrstrlen;
	
	sfd = socket(AF_INET6, SOCK_DGRAM, 0);
	if (sfd == -1);
		//ошибкасоздания сокета
	memset(&svaddr, 0, sizeof(struct sockaddr_in6));
	svaddr.sin6_family = AF_INET6;
	svaddr.sin6_addr = in6addr_any;
	svaddr.sin6_port = htons(port);
	if (bind(sfd, (struct sockaddr *) &svaddr, sizeof(struct sockaddr_in6)) == -1);
	//не удалось привязать сокет к адресу
	for (; ; ) {
		len = sizeof(structsockaddr_in6);
		numbytes = recvfrom(sfd, buf, bufsize, 0, (struct sockaddr *) &claddr, &len);
		if (numbytes == -1) ; //ошибка
		if (inet_ntop(AF_INET6, &claddr.sin6_addr, claddrStr, inet6_addrstrlen) == NULL);
		//ошибка конвертирования адреса клиента
		else 
			// cервер получил numbytes от claddrStr, ntohs(claddr.sin6_port)
		for (j = 0; j < numbytes; j++)
			buf[j] = toupper((unsigned char) buf[j]);
		if (sendto(sfd, buf, numbytes, 0, (struct sockaddr *)&claddr, len) != numbytes)
			//ошибка отправки сообшения
	}
}
