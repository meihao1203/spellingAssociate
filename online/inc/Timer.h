 ///
 /// @file    Timer.h
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-22 08:57:31
 ///
 
#ifndef __TIMER_H__
#define __TIMER_H__
#include<iostream>
#include<functional>
using namespace std;
namespace meihao
{
	typedef function<void()> TimerCallback;
	class Timer
	{
		public:
			Timer(TimerCallback,int,int);
			~Timer();
			void start();
			void stop();
		private:
			int _fd;
			TimerCallback _cb;
			bool _isStarted;
	};
};
#endif
