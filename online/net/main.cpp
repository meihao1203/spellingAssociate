 //
 /// @file    main.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-20 20:04:03
 ///
 
#include"SocketIO.h"
#include<iostream>
#include"InetAddress.h"
#include"Socket.h"
#include"string.h"
using namespace std;
int main()
{
	meihao::InetAddress ina(8848);
	meihao::Socket sock;
	sock.ready(ina);
	int nfd = sock.accept();
	meihao::SocketIO sio(nfd);
	char buf[512] = "i am server\n";
	sio.writen(buf,strlen(buf));
	while(1)
	{
		bzero(buf,sizeof(buf));
		sio.readline(buf,sizeof(buf));
		cout<<buf;
		sio.writen(buf,strlen(buf));
	}
}
