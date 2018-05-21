 ///
 /// @file    MyThread.h
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-21 20:04:44
 ///
 
#ifndef __MYTHREAD_H__
#define __MYTHREAD_H__
#include<iostream>
#include<pthread.h>
#include<functional>
using namespace std;
namespace meihao
{
	typedef ::function<void()> ThreadCallback;
	class MyThread
	{
		public:
			MyThread(ThreadCallback);
			~MyThread();
			void start();
			void join();
			static void* threadFunc(void*);
		private:
			pthread_t _pthId;
			bool _isRunning;
			ThreadCallback _cb;
	};
};
#endif
