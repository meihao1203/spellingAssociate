 ///
 /// @file    MyThread.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-21 20:07:41
 ///
 
#include"MyThread.h"
#include<iostream>
#include<stdio.h>
#include<errno.h>
using namespace std;
namespace meihao
{
	MyThread::MyThread(ThreadCallback cb):_cb(cb)
									,_pthId(0)
									,_isRunning(false)
	{
	}
	MyThread::~MyThread()
	{
		if(_isRunning)
		{
			pthread_detach(_pthId);
		}
	}
	void MyThread::start()
	{
		_isRunning = true;
		int ret = ::pthread_create(&_pthId,NULL,&MyThread::threadFunc,this);
		if(0!=ret)
		{
			perror("::pthread_create");
		}
	}
	void MyThread::join()
	{
		if(_isRunning)
		{
			pthread_join(_pthId,NULL);
		}
	}
	void* MyThread::threadFunc(void* arg)
	{
		MyThread* thread = static_cast<MyThread*> (arg);
		if(thread)
		{
			thread->_cb();
		}
	}
};
