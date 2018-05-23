 ///
 /// @file    spellingAssociate.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-23 20:19:37
 ///
 
#include"spellingAssociate.h"
#include<iostream>
#include"MyDict.h"
using namespace std;
namespace meihao
{
	spellingAssociate::spellingAssociate(const string& confFilename):_conf(confFilename)
					,_tcpServer( _conf.getMap()["ip"].c_str(),atoi(_conf.getMap()["port"].c_str()) )
					,_threadpool(4,10,_conf)
					,_timer(bind(&Threadpool::updateCache,&_threadpool),10,5 )
	{
	//线程池：4个线程，任务队列10
	//10s开始更新cache,之后每隔5s再更新一次
		MyDict* pMyDict = MyDict::getInstance();
		pMyDict->init(_conf.getMap()["dict.txt"].c_str(),
				NULL);  //这里以后要放中文词典
	}
};
