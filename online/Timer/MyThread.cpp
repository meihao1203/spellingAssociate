 ///
 /// @file    MyThread.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-21 20:07:41
 ///
 
#include"MyThread.h"
#include<iostream>
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

};
int main()
{}
