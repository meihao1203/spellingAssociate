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
//#include<errno.h>
#include<poll.h>
#include<stdlib.h>
#include<time.h>
#include"myLog.h"
using namespace std;
namespace meihao
{
	static meihao:: myLog* Timerlog  = meihao::myLog::getInstance();
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
		stringstream ss;
		ss<<ctime(&t);
		Timerlog->info(catMsg(ss.str()));
	}
	void Timer::start()
	{
		_isStarted = true;
		struct pollfd event;
		event.fd = _fd;
		event.events = POLLIN;
		printTime();
		//cout<<"------定时更新缓存线程启动------";
		Timerlog->info(catMsg("------定时更新缓存线程启动------"));
		while(_isStarted)
		{
			int ret = ::poll(&event,1,61000);  //61s超时
			if(0==ret)
			{
				Timerlog->warn(catMsg("poll timeout"));
			}
			else if(-1==ret)
			{
				if(errno==EINTR)
					continue;
				Timerlog->error(catMsg("poll"));
				exit(EXIT_FAILURE);
			}
			else
			{
				if(event.revents==POLLIN)
				{
					readTimerfd(_fd);  // 读走timerfd上的数据
					//cout<<"------开始更新缓冲cache------";
					Timerlog->info(catMsg("------开始更新缓冲cache------"));
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
			//perror("stopTimerfd ::setTimerfd");
			Timerlog->error(catMsg("setTimerfd"));
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
