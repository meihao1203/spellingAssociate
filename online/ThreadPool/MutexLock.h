 ///
 /// @file    MutexLock.h
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-16 19:23:10
 ///
 
#ifndef __MUTEXLOCK_H__
#define __MUTEXLOCK_H__
#include<iostream>
#include<pthread.h>
using namespace std;
namespace meihao
{
	class MutexLock
	{
		public:
			MutexLock();
			~MutexLock();
			void lock();
			void unlock();
			pthread_mutex_t* getMutexPtr();
		private:
			pthread_mutex_t _mutex;
	};
};
#endif
