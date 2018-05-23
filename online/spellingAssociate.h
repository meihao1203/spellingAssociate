 ///
 /// @file    spellingAssociate.h
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-23 20:15:02
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
			MyConf _conf;
			TcpServer _tcpServer;
			Threadpool _threadpool;
			TimerThread _timer;
	};
};
#endif
