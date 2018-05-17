 ///
 /// @file    ThreadpoolThread.h
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-17 14:28:35
 ///
 
#ifndef __THREADPOOLTHREAD_H__
#define __THREADPOOLTHREAD_H__
#include<iostream>
#include"Thread.h"
#include"ThreadpoolThread.h"
using namespace std;
namespace meihao
{
	class ThreadpoolThread:public Thread
	{
		public:
			ThreadpoolThread(Threadpool&);
			void run();
		private:
			Threadpool& _threadpool;
	};
};
#endif
