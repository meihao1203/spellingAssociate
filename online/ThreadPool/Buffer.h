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
using namespace std;
namespace meihao
{
	typedef Task* DataType;
	class Buffer
	{
		private:
			MutexLock _mutex;
			Condition _notFull;
			Condition _notEmpty;
			queue<Task*> DataType;
			int _queSize;
			bool _flag;
	};
};
#endif
