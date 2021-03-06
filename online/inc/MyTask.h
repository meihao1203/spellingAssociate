 ///
 /// @file    MyTask.h
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-22 16:26:40
 ///
 
#ifndef __MYTASK_H__
#define __MYTASK_H__
#include<iostream>
#include"Cache.h"
#include"Compare.h"
#include<vector>
#include<set>
#include<queue>
#include"InetAddress.h"
using namespace std;
namespace meihao
{
	class Cache;
	class MyTask
	{
		public:
			MyTask(const string& queryWord,int peerfd);
			void execute(Cache& cache);
		private:
			void queryIndexTable();
			void statistic(set<int>& iset);
			int distance(const string& rhs);
			void response(Cache& cache);
			string getPeerfdAddr();
		private:
			string _queryWord;
			int _peerfd;
			priority_queue<MyResult,vector<MyResult>,Compare> _resultQue;
			//增加_peerAddr,日志记录的时候知道是谁请求发来数据
			InetAddress _peerAddr;
	};
};
#endif
