 ///
 /// @file    ThreadpoolThread.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-17 14:32:10
 ///
 
#include"ThreadpoolThread.h"
#include<iostream>
using namespace std;
namespace meihao
{
	ThreadpoolThread::ThreadpoolThread(Threadpool& threadpool):_threadpool(threadpool)
	{
	}
	void ThreadpoolThread::run()
	{//具体的工作线程
		_threadpool.threadFunc();  //指向线程池里指定的函数
	}
};
