 ///
 /// @file    Threadpool.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-17 11:49:51
 ///
 
#include"Threadpool.h"
#include<iostream>
using namespace std;
namespace meihao
{
	Threadpool::Threadpool(int threadNum,int bufSize):_threadNum(threadNum)
													,_bufSize(bufSize)
													,_buf(_bufSize)
													,_isExit(false)
	{}
	void Threadpool::start()
	{//开启线程池,造好线程
		for(int idx=0;idx!=_threadNum;++idx)
		{
			Thread* thread = new 
		}

	}
};
