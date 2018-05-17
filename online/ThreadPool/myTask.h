 ///
 /// @file    myTask.h
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-17 15:17:14
 ///
 
#ifndef __MYTASK_H__
#define __MYTASK_H__
#include<iostream>
#include"Task.h"
using namespace std;
namespace meihao
{
	class myTask:public Task
	{
		public:
			void process();
	};
};
#endif
