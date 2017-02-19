#include <cstdio>
#include "socket.h"
#include "config.h"

int main()
{
	get_config();
	printf("initializing finished\n");
	int lis, conn;
	sockaddr_in servaddr, cliaddr;
	socklen_t cli_len;
	char buff[MAXLINE + 100];

	printf("建立监听套接字...");
	lis = Socket(AF_INET, SOCK_STREAM, 0);
	printf("完成\n");

	printf("准备服务器地址...\n");
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(port);

	Bind(lis, (SA *) &servaddr, sizeof(servaddr));

	Listen(lis, LISTENQ);
	printf("完成,服务器端口是%d\n", ntohs(servaddr.sin_port));

	size_t offs, n;

	while(true)
	{
		conn = Accept(lis, (SA *) &cliaddr, &cli_len);

		offs = sprintf(buff, "%s:%d $:", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
		printf("accpet from %s:%d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

		if((n = read(conn, buff + offs, MAXLINE)) <= 0) err_msg("read error");

		buff[offs+n] = 0;

		if((n = write(conn, buff, strlen(buff))) <= 0) err_msg("write error");

		close(conn);
	}

	return 0;
}

