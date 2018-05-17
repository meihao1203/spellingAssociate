 ///
 /// @file    Threadpool.h
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-17 11:23:00
 ///
 
#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__
#include<iostream>
#include<vector>
#include"Task.h"
#include"Buffer.h"
#include"Noncopyable.h"
#include"Thread.h"
using namespace std;
namespace meihao
{
	class Threadpool:private Noncopyable  //Threadpool禁止拷贝，Noncopyable禁止指向派生类对象
	{
		public:
			Threadpool(int,int);
			void start();
			void stop();
			void addTask(Task* task);
			Task* getTask();
			void threadFunc();
		private:
			int _threadNum;
			vector<Thread*> _threadsVec;
			int _bufSize;
			Buffer _buf;
			bool _isExit;
	};
};
#endif
