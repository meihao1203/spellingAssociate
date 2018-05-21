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
#include"TcpConnection.h"
using namespace std;
namespace meihao
{
	void onConnection(const meihao::TcpConnectionPtr& conn)
	{
		cout<<conn->toString()<<" has connected!"<<endl;
		conn->send("connect success!\n");
	}
	void onMessage(const meihao::TcpConnectionPtr& conn)
	{
		string msg = conn->receive();
		cout<<"recv:"<<msg<<endl;
		conn->send(msg);
	}
	void onClosed(const meihao::TcpConnectionPtr& conn)
	{
		cout<<conn->toString()<<" has closed!"<<endl;
	}
};
void test0()
{
	meihao::InetAddress ina(8848);
	meihao::Socket sock;
	sock.ready(ina);
	int nfd = sock.accept();
//	meihao::SocketIO sio(nfd);
	char buf[512] = "i am server\n";
//	sio.writen(buf,strlen(buf));
//	while(1)
//	{
//		bzero(buf,sizeof(buf));
//		sio.readline(buf,sizeof(buf));
//		cout<<buf;
//		sio.writen(buf,strlen(buf));
//	}
}
int main()
{
	meihao::InetAddress ina(8848);
	meihao::Socket sock;
	sock.ready(ina);
	int nfd = sock.accept();
	meihao::TcpConnectionPtr conn(new meihao::TcpConnection(nfd));
	conn->setConnectionCallback(meihao::onConnection);
	conn->setMessageCallback(meihao::onMessage);
	conn->setCloseCallback(meihao::onClosed);
	conn->handleConnectionCallback();
	conn->handleMessageCallback();
	conn->handleCloseCallback();
}
