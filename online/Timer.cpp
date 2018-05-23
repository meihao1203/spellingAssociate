 ///
 /// @file    Timer.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-22 09:02:09
 ///
 
#include"Timer.h"
#include<iostream>
#include<sys/timerfd.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<poll.h>
#include<stdlib.h>
#include<time.h>
using namespace std;
namespace meihao
{
	int createTimerfd()
	{
		int tfd = ::timerfd_create(CLOCK_REALTIME,0);
		if(-1==tfd)
		{
			perror("::timerfd_create");
		}
		return tfd;
	}
	int setTimerfd(int fd,int init_sec,int interval_sec)
	{
		struct itimerspec new_value;
		new_value.it_interval.tv_sec = interval_sec;
		new_value.it_interval.tv_nsec = 0;
		new_value.it_value.tv_sec = init_sec;
		new_value.it_value.tv_nsec = 0;
		int ret = ::timerfd_settime(fd,0,&new_value,NULL);
		if(-1==ret)
		{
			perror("::timer_settime");
			return -1;
		}
		return 0;
	}
	Timer::Timer(TimerCallback cb,int init_sec,int interval_sec):_cb(cb)
								,_fd(createTimerfd())
								,_isStarted(false)
	{
		setTimerfd(_fd,init_sec,interval_sec);
	}
	Timer::~Timer()
	{
		if(_isStarted)
			stop();
	}
	int readTimerfd(int fd)
	{
		ssize_t val;
		int ret = ::read(fd,&val,sizeof(ssize_t));
		if(-1==ret)
		{
			perror("::read");
		}
	}
	void printTime()
	{
		time_t t = time(NULL);
		cout<<ctime(&t);
	}
	void Timer::start()
	{
		_isStarted = true;
		struct pollfd event;
		event.fd = _fd;
		event.events = POLLIN;
		printTime();
		while(_isStarted)
		{
			int ret = ::poll(&event,1,5000);
			if(0==ret)
			{
				cout<<"::poll timeout"<<endl;
			}
			else if(-1==ret)
			{
				if(errno==EINTR)
					continue;
				perror("::poll");
				exit(EXIT_FAILURE);
			}
			else
			{
				if(event.revents==POLLIN)
				{
					readTimerfd(_fd);  // 读走timerfd上的数据
					printTime();
					if(_cb)
						_cb();  //执行回调函数
				}
			}
		}
	}
	int stopTimerfd(int fd,int init_sec,int interval_sec)
	{
		int ret = setTimerfd(fd,0,0);
		if(-1==ret)
		{
			perror("stopTimerfd ::setTimerfd");
			return -1;
		}
		return 0;
	}
	void Timer::stop()
	{
		if(_isStarted)
		{
			_isStarted = false;
			stopTimerfd(_fd,0,0);
		}
	}
};
