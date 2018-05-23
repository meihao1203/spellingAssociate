 ///
 /// @file    spellingAssociate.h
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-23 16:25:20
 ///
 
#ifndef __SPELLINGASSOCIATE_H__
#define __SPELLINGASSOCIATE_H__
#include<iostream>
#include"MyConf.h"
#include"TcpServer.h"
#include"Threadpool.h"
#include"TimerThread.h"
using namespace std;
namespace meihao
{
	class spellingAssociate
	{
		public:
			spellingAssociate(const string& confFilename);
			void start();
			void stop();
			void onConnection(TcpConnectionPtr);
			void onMessage(TcpConnectionPtr);
			void onClose(TcpConnectionPtr);
		private:
			MyConf _conf;  //配置文件
			TcpServer _tcpServer;  //服务器
			Threadpool _threadpool;  //线程池
			TimerThread _timer;  //同步线程池和业务线程的cache
	};
};
#endif
