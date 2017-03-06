server.exe : server.cpp socket.h config.h error.h lib/work.so /etc/ld.so.conf.d/asmdef_c_server.conf lib/
	ldconfig
	g++ -std=c++11 -pthread server.cpp lib/work.so -O2 -o server.exe

/etc/ld.so.conf.d/asmdef_c_server.conf :
	echo "${dirname}/lib\n" > /etc/ld.so.conf.d/asmdef_c_server.conf

lib/work.so : work.cpp
	g++ -std=c++11 -pthread work.cpp -fpic -c -o work.o
	g++ -std=c++11 -pthread work.o -shared -fpic -o lib/work.so

.PHONY:clean

clean :
	-rm server.conf *.o *.so *.exe
	-rm lib/*.so
	-rm /etc/ld.so.conf.d/asmdef_c_server.conf
	ldconfig

