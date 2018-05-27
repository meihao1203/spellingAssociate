///
/// @file    Threadpool.cpp
/// @author  meihao1203(meihao19931203@outlook.com)
/// @date    2018-05-17 11:49:51
///

#include"Threadpool.h"
#include<unistd.h>
#include<iostream>
using namespace std;
namespace meihao
{
	Threadpool::Threadpool(int threadNum,int bufSize,MyConf& myconf):_threadNum(threadNum)
													,_bufSize(bufSize)
													,_buf(_bufSize)
													,_conf(myconf)
												    ,_isExit(false)
	{}
	void Threadpool::start()
	{//开启线程池,造好线程
		//线程启动先初始化线程池cache
		readCache();
		for(int idx=0;idx!=_threadNum;++idx)
		{
			Thread* thread = new Thread( 
					::bind(&Threadpool::threadFunc,this,::placeholders::_1)
					//子线程各自执行的时候回修改Cache,导致和线程池里的Cache不一样
					//所以造线程的时候先拷贝线程池的cache过去,之后调用回调函数
					//执行各自的线程函数的时候传递自己拷贝的cache过去
					//防止多个线程同时修改线程池cache,不用对cache操作加解锁
					//所以这里绑定回调函数先使用占位符,最后在传参
					,_cache );
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
	void Threadpool::addTask(Task task)
	{
		_buf.push(task);  //线程池添加一个任务
	}
	Task Threadpool::getTask()
	{
		return _buf.pop();
	}
	void Threadpool::threadFunc(Cache& cache)  //线程对象的绑定函数,也是真正线程的执行功能
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
			Task task = getTask();
			if(task)
			{
				task(cache);
			}
		}
	}
	void Threadpool::readCache()
	{
		_cache.readFromFile( ((_conf.getMap())["cache"]).c_str() );
	}
	void Threadpool::updateCache()
	{
		for( auto& elem:_threadsVec )
		{//每个子线程的cache来更新线程池的cache
			_cache.update(elem->getCache());
		}
		for( auto& elem:_threadsVec )
		{
			elem->getCache().update(_cache);
		}
		//写回磁盘
		_cache.writeToFile( (_conf.getMap())["cache"] );
	}
};
