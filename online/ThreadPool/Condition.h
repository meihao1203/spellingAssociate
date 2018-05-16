 ///
 /// @file    Condition.h
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-16 19:46:18
 ///
 
#ifndef __CONDITION_H__
#define __CONDITION_H__
#include<iostream>
#include"MutexLock.h"
using namespace std;
namespace meihao
{
	class Condition
	{
		public:
			Condition(MutexLock&);
			~Condition();
			void wait();
			void notify();
			void notifyall();
		private:
			pthread_cond_t _cond;
			MutexLock& _mutex;
	};
};
#endif
