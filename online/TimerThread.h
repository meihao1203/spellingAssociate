 ///
 /// @file    TimerThread.h
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-22 09:51:14
 ///
 
#ifndef __TIMERTHREAD_H__
#define __TIMERTHREAD_H__
#include<iostream>
#include"Timer.h"
#include"MyThread.h"
using namespace std;
namespace meihao
{
	typedef function<void()> TimerThreadCallback;
	class TimerThread
	{
		public:
			TimerThread(TimerThreadCallback,int,int);
			void start();
			void stop();
		private:
			Timer _timer;
			MyThread _thread;
	};
};
#endif
