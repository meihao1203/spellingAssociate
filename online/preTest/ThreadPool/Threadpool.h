 ///
 /// @file    Threadpool.h
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-17 11:23:00
 ///
 
#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__
#include<iostream>
#include<vector>
#include"Buffer.h"
#include"Noncopyable.h"
#include"Thread.h"
#include"Cache.h"
#include<functional>
#include"MyConf.h"
using namespace std;
namespace meihao
{
	typedef ::function<void(Cache&)> Task;
	class Threadpool:private Noncopyable  //Threadpool禁止拷贝，Noncopyable禁止指向派生类对象
	{
		public:
			Threadpool(int,int,MyConf&);  //先前线程池改进,加一个MyConf&
			void start();
			void stop();
			void addTask(Task task);
		private:
			Task getTask();
		public:
			void threadFunc(Cache& cache);  //线程池函数，也是子线程所要执行的函数
			//以回调函数的形式传递给子线程对象
			void readCache();
			void updateCache();
		private:
			int _threadNum;
			vector<Thread*> _threadsVec;
			int _bufSize;
			Buffer _buf;
			bool _isExit;
			Cache _cache;  //线程池有一个Cache，到时候要传给子线程
			MyConf& _conf;  //要有一个配置文件类对象,到时候读Cache
	};
};
#endif
