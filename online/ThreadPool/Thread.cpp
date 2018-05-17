 ///
 /// @file    Thread.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-17 11:03:18
 ///
 
#include"Thread.h"
#include<iostream>
#include<stdlib.h>
using namespace std;
#define handle_error(msg)\
	do{\
		perror(msg);\
		exit(EXIT_FAILURE);\
	}while(0);
namespace meihao
{
	Thread::Thread():_pthId(0)
					 ,_isRunning(false)
	{
	}
	void Thread::start()
	{
		_isRunning = true;
		pthread_create(&_pthId,NULL,&Thread::threadFunc,this);
	}
	void Thread::join()
	{
		if(_isRunning)
		{
			pthread_join(_pthId,NULL);
		}
	}
	Thread::~Thread()
	{
		if(_isRunning)
		{
			pthread_detach(_pthId);
		}
	}
	void* Thread::threadFunc(void* arg)
	{//线程处理函数,指向线程类中的run方法，
	 //run方法由派生类实现
		Thread* thread = static_cast<Thread*> (arg);
		if(thread)
		{
			thread->run();
		}
	}
};
