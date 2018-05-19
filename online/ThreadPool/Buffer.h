 ///
 /// @file    Buffer.h
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-17 09:00:21
 ///
 
#ifndef __BUFFER_H__
#define __BUFFER_H__
#include<iostream>
#include"MutexLock.h"
#include"Condition.h"
#include"Task.h"
#include<queue>
#include<functional>
#include"Cache.h"
using namespace std;
namespace meihao
{
	//typedef Task* DataType;
	typedef std::function<void(Cache&)> Task;
	class Buffer
	{
		public:
			Buffer(int);
			void push(Task);
			Task pop();
			void wakeupEmpty();  // 唤醒所有等待在_notEmpty条件变量上的线程
			bool full();
			bool empty();
		private:
			MutexLock _mutex;
			Condition _notFull;
			Condition _notEmpty;
			//queue<DataType> _que;
			queue<Task> _que;
			int _queSize;
			bool _flag;  // 标志位,线程池关闭为false
	};
};
#endif
