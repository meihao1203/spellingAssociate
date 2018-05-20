 ///
 /// @file    client.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-20 17:00:38
 ///
 
#include<iostream>
#include"InetAddress.h"
using namespace std;
int main()
{
	meihao::InetAddress ina("192.168.254.136",8848);
	int cfd = socket(AF_INET,SOCK_STREAM,0);
	connect(cfd,(const struct sockaddr*)ina.getInetAddressPtr(),(socklen_t)sizeof(struct sockaddr));
	char buf[512];
	recv(cfd,buf,sizeof(buf),0);
	cout<<buf<<endl;
}
