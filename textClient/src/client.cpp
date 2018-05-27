///
/// @file    client.cpp
/// @author  meihao1203(meihao19931203@outlook.com)
/// @date    2018-05-20 17:00:38
///

#include<iostream>
#include<string.h>
#include<unistd.h>
#include"InetAddress.h"
#include"SocketIO.h"
#include<sys/epoll.h>
#include<string.h>
#include<strings.h>
using namespace std;
int main()
{
	meihao::InetAddress ina("192.168.254.136",8848);
	int cfd = socket(AF_INET,SOCK_STREAM,0);
	connect(cfd,(const struct sockaddr*)ina.getInetAddressPtr(),(socklen_t)sizeof(struct sockaddr));

	//epoll实现多路复用
	int  epfd = epoll_create(1);
	if(-1==epfd)
	{
		perror("epoll_create");
		return -1;
	}
	//注册描述符
	struct epoll_event eve,events[2];
	eve.events = EPOLLIN;
	eve.data.fd = cfd;
	int ret = epoll_ctl(epfd,EPOLL_CTL_ADD,cfd,&eve);
	if(-1==ret)
	{
		perror("epoll_ctl");
		return -1;
	}
	eve.events = EPOLLIN;
	eve.data.fd = 0;
	ret = epoll_ctl(epfd,EPOLL_CTL_ADD,0,&eve);
	memset(events,0,sizeof(eve));
	//开始监听
	char buf[1024];
	meihao::SocketIO sio(cfd);
	while(1)
	{
		ret = epoll_wait(epfd,events,2,-1);
		if(-1==ret)
		{
			if(errno==EINTR)
				continue;
			return -1;
		}
		if(ret>0)
		{
			for(int idx=0;idx<ret;++idx)
			{
				if(events[idx].data.fd==cfd&&events[idx].events==EPOLLIN)
				{
					bzero(buf,sizeof(buf));
					//sio.readline(buf,sizeof(buf));
					read(cfd,buf,sizeof(buf));
					cout<<"recv from server:"<<buf<<endl;
				}
				if(events[idx].data.fd==0&&events[idx].events==EPOLLIN)
				{
					bzero(buf,sizeof(buf));	
					read(0,buf,sizeof(buf));
					sio.writen(buf,strlen(buf));
				}
			}
		}
	}
}
