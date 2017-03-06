#include "socket.h"
#include <cstdio>

void work(int conn)
{
	char buff[MAXLINE], output[MAXLINE];
	sockaddr_in cliaddr;
	socklen_t cli_len = sizeof(cliaddr);

	memset(&cliaddr, 0, cli_len);
	if(getpeername(conn, (SA *) &cliaddr, &cli_len))
		err_sys("getpeername error");

	size_t offs = sprintf(buff, "your address - %s:%d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

	read(conn, buff + offs, MAXLINE - offs);
	offs = printf("%s\n", buff);

	sprintf(output, "%s\r\n%s\r\n\r\n%s", "HTTP/1.1 200 OK",
			"Host:Asm.Def",
			"<!DOCTYPE html>\r\n<html>\r\n<body>Hello World!</body>\r\n</html>");

	write(conn, output, strlen(output));

}
