 ///
 /// @file    Thread.h
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-17 09:56:27
 ///
 
#ifndef __THREAD_H__
#define __THREAD_H__
#include<iostream>
#include"Noncopyable.h"
#include<pthread.h>
#include<functional>
#include"Cache.h"
using namespace std;
namespace meihao
{
	typedef ::function<void(Cache&)> ThreadCallback;
	class Thread:private Noncopyable //防止Thread被拷贝，私有继承，防止Noncopyable指向派生类对象
	{
		public:
			Thread(ThreadCallback cb,Cache& cache);  // 线程要传一个回调函数,每个线程都有一个cache
			//所以线程里面传一个cache引用,避免了拷贝，费时间,费内存
			void start();  //线程启动,执行线程池里面的threadFunc
			//threadFunc会以回调函数的形式传递过来
			void join();
			//virtual void run() = 0;  //基于对象，不要纯虚函数
			virtual ~Thread();
			static void* threadFunc(void*);
			Cache& getCache();  // 返回线程Cache,用做最后同步更新线程池Cache
		private:
			pthread_t _pthId;
			bool _isRunning;
			ThreadCallback _cb;
			Cache _cache;
	};
};
#endif
