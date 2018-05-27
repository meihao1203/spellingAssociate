 ///
 /// @file    spellingAssociate.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-23 20:19:37
 ///
#include"spellingAssociate.h"
#include<iostream>
#include"MyDict.h"
#include"MyTask.h"
#include"myLog.h"  //log4cpp来记录日志，日志路径/home/meihao/spellingAssociate/online/conf/log

static meihao::myLog* log  = meihao::myLog::getInstance();
#define logSetpriority(priority) log->setPriority(priority)
#define logError(msg) log->error(catMsg(msg))
#define logWarn(msg) log->warn(catMsg(msg))
#define logInfo(msg) log->info(catMsg(msg))
#define logDebug(msg) log->debug(catMsg(msg))
#define logFatal(msg) log->fatal(catMsg(msg))
#define logDestroy() myLog::destroy()
using namespace std;
using namespace std::placeholders;
namespace meihao
{

	spellingAssociate::spellingAssociate(const string& confFilename):_conf(confFilename)
					,_tcpServer( _conf.getMap()["ip"].c_str(),atoi(_conf.getMap()["port"].c_str()) )
					,_threadpool(4,10,_conf)
					,_timer(bind(&Threadpool::updateCache,&_threadpool),10,60 )
	{
	//线程池：4个线程，任务队列10
	//10s开始更新cache,之后每隔60s再更新一次
		MyDict* pMyDict = MyDict::getInstance();
		pMyDict->init(_conf.getMap()["dict.txt"].c_str(),
				// NULL);  //这里以后要放中文词典
				_conf.getMap()["cnDict.txt"].c_str());
	}
	void spellingAssociate::start()
	{
		_threadpool.start();  //线程池启动,造线程
		logInfo("threadpool start");
		_timer.start();  //timer线程,到时间更新同步线程
		logInfo("timer start");
		//TCPServer对象绑定回调函数
		_tcpServer.setConnectionCallback(
				bind(&spellingAssociate::onConnection,this,_1)
				);
		_tcpServer.setMessageCallback(
				bind(&spellingAssociate::onMessage,this,_1)
				);
		_tcpServer.setCloseCallback(
				bind(&spellingAssociate::onClose,this,_1)
				);
		logInfo("server callback function set down");
		_tcpServer.start();  //服务端启动
		logInfo("tcpServer start");
	}
	void spellingAssociate::stop()
	{
		_threadpool.stop();
		_timer.stop();
		_tcpServer.stop();
		logInfo("stop");
	}
	void spellingAssociate::onConnection(const meihao::TcpConnectionPtr& conn)
	{
		stringstream ss;
		ss<<conn->toString()<<" has connected!"<<endl;
		//cout<<conn->toString()<<" has connected!"<<endl;
		logInfo(ss.str());
		conn->send("you has connected to the spellingAssociate server!");
	}
	void spellingAssociate::onMessage(const meihao::TcpConnectionPtr& conn)
	{
		string msg = conn->receive();  //接收一行
		//cout<<"recv msg:"<<msg<<endl;
		int pos = msg.find('\n');  //去掉换行符
		//cout<<"pos"<<pos<<endl;
		string queryWord = msg.substr(0,pos);
		//cout<<"client query word :"<<queryWord<<endl;  //测试一下有没有去掉换行  15:44 0524
		//对应的建立一个任务
		MyTask task(queryWord,conn->fd());  //传递接收到的fd过去，线程就可以和客户端交互了
		_threadpool.addTask(bind(&MyTask::execute,&task,_1));  //占位符_1最终是传递的执行任务线程的cache
	}
	void spellingAssociate::onClose(const meihao::TcpConnectionPtr& conn)
	{
		stringstream ss;
		ss<<conn->toString()<<" has closed!"<<endl;
		logInfo(ss.str());
	}
};
