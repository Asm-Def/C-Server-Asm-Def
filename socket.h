#ifndef WRAP_SOCKET_H
#define WRAP_SOCKET_H

#include <cstdlib>
#include <unistd.h>			//read/write
#include <cstring>
#include <sys/types.h>		//basic system data types
#include <sys/socket.h>		//basic socket definitions
#include <errno.h>			//errno
#include <arpa/inet.h>		//inet(3) functions
#include <fcntl.h>			//for nonblocking
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <netinet/in.h>		//sockaddr_in{} and other Internet defns

#define MAXLINE 4096
#define LISTENQ 1024
#define BUFFSIZE 8192
#define SA sockaddr

void err_dump(const char *, ...);
void err_msg(const char *, ...);
void err_quit(const char *, ...);
void err_quit(const char *, ...);
void err_sys(const char *, ...);

#include "error.h"

int Socket(int family, int type, int protocol)
{
	int n;
	if ((n = socket(family, type, protocol)) < 0)
		err_sys("socket error");
	return n;
}

int Bind(int listenfd, SA *servaddr, socklen_t sz)
{
	int n;
	if ((n = bind(listenfd, servaddr, sz)) < 0)
		err_sys("bind error");
	return n;
}

int Listen(int listenfd, const int mx)
{
	int n;
	if ((n = listen(listenfd, mx)) < 0)
		err_sys("listen error");
	return n;
}

int Accept(int fd, SA *cli, socklen_t *addrlen)
{
	int n;
	if ((n = accept(fd, cli, addrlen)) < 0)
		err_sys("accept error");
	return n;
}

#endif	//WRAP_SOCKET_H
