#include <cstdio>
#include "socket.h"
#include "config.h"

void work(int conn);

int main()
{
	get_config();
	printf("initializing finished\n");
	int lis, conn;
	sockaddr_in servaddr, cliaddr;
	socklen_t serv_len, cli_len;

	printf("建立监听套接字...");
	int reuse = 1;
	lis = Socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(lis, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));	//端口重用
	printf("完成\n");

	printf("准备服务器地址...\n");
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(port);

	Bind(lis, (SA *) &servaddr, sizeof(servaddr));

	Listen(lis, LISTENQ);
	printf("完成,服务器端口是%d\n", ntohs(servaddr.sin_port));

	int fpid = 1;

	while(fpid > 0)
	{
		memset(&cliaddr, 0, sizeof(cliaddr));
		conn = Accept(lis, (SA *) &cliaddr, &cli_len);

		if(getpeername(conn, (SA *) &cliaddr, &cli_len))
			err_msg("getpeername error");

		printf("accpet from %s:%d\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

		if((fpid = fork()) < 0) err_sys("error in fork");
		else if(fpid == 0)
			work(conn);

		close(conn);
	}

	return 0;
}

