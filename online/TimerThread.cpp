 ///
 /// @file    TimerThread.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-22 10:20:57
 ///
 
#include"TimerThread.h"
#include<iostream>
using namespace std;
namespace meihao
{
	TimerThread::TimerThread(TimerThreadCallback cb,int init_sec,int interval_sec):_timer(cb,init_sec,interval_sec)
																				,_thread(::bind(&Timer::start,&_timer))
	{
	}
	void TimerThread::start()
	{
		_thread.start();
	}
	void TimerThread::stop()
	{
		//_thread.join();
		_timer.stop();  //timer一停，start函数结束，线程也就结束
	}
};
