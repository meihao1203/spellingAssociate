 ///
 /// @file    Task.h
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-17 09:07:38
 ///
 
#ifndef __TASK_H__
#define __TASK_H__
#include<iostream>
using namespace std;
namespace meihao
{
	class Task
	{
		public:
			virtual void process()=0;  // 具体的任务由继承者来实现
			virtual ~Task()
			{}
	};
};
#endif
