///
/// @file    Threadpool.cpp
/// @author  meihao1203(meihao19931203@outlook.com)
/// @date    2018-05-17 11:49:51
///

#include"Threadpool.h"
#include"ThreadpoolThread.h"
#include<unistd.h>
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
			Thread* thread = new ThreadpoolThread(*this);  //要把线程池对象传过去，
			//run方法调用线程池功能函数要用到
			_threadsVec.push_back(thread);
		}
		for(auto& elem:_threadsVec)
		{
			elem->start();  //线程池造好的所有线程启动
		}
	}
	void Threadpool::stop()
	{
		if(!_isExit)
		{
			while(!_buf.empty())  //如果缓冲区不空
				//说明还有任务线程没执行完
			{
				sleep(1);
			}
			_buf.wakeupEmpty();  //唤醒所有等待在缓冲区条件变量上的线程
			_isExit = true;
			//回收线程
			for(auto& elem:_threadsVec)
			{
				elem->join();  //线程回收
				delete elem;  //线程对象是new出来的，释放资源
			}
		}
	}
	void Threadpool::addTask(Task* task)
	{
		_buf.push(task);  //线程池添加一个任务
	}
	Task* Threadpool::getTask()
	{
		return _buf.pop();
	}
	void Threadpool::threadFunc()
	{
		//	if(!_isExit)
		//	{
		//		Task* task = getTask();
		//		if(task)
		//		{
		//			task->process();  //线程执行的具体的任务
		//		}
		//	}
		//线程执行任务是死循环，这里直接执行一次就退出了
		while(!_isExit)
		{
			Task* task = getTask();
			if(task)
			{
				task->process();
			}
		}
	}
};
