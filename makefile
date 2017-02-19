server.exe : server.cpp socket.h config.h error.h
	g++ server.cpp -O2 -o server.exe

.PHONY:clean

clean :
	-rm server.exe server.conf

