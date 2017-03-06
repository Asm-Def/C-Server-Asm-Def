#include "socket.h"
#include <cstdio>

void work(int conn, std::mutex *sock_lck, std::mutex *log_lck)
{
	log_lck->lock();							//tips: printf是否线程安全?
	printf("connect fd = %d\n", conn);
	log_lck->unlock();

	char buff[MAXLINE], output[MAXLINE];
	sockaddr_in cliaddr;
	socklen_t cli_len = sizeof(cliaddr);

	memset(&cliaddr, 0, cli_len);

	if(getpeername(conn, (SA *) &cliaddr, &cli_len)){
		log_lck->lock();
		err_sys("getpeername error");
		log_lck->unlock();
	}

	size_t offs = sprintf(buff, "your address - %s:%d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

	read(conn, buff + offs, MAXLINE - offs);
	offs = printf("%s\n", buff);

	sprintf(output, "%s\r\n%s\r\n\r\n%s", "HTTP/1.1 200 OK",
			"Host:Asm.Def",
			"<!DOCTYPE html>\r\n<html>\r\n<body>Hello World!</body>\r\n</html>");

	write(conn, output, strlen(output));

	close(conn);

}
