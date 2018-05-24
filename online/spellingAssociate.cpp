 ///
 /// @file    spellingAssociate.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-23 20:19:37
 ///
 
#include"spellingAssociate.h"
#include<iostream>
#include"MyDict.h"
#include"MyTask.h"
using namespace std;
using namespace std::placeholders;
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
	void spellingAssociate::start()
	{
		_threadpool.start();  //线程池启动,造线程
		_timer.start();  //timer线程,到时间更新同步线程
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
		_tcpServer.start();  //服务端启动
	}
	void spellingAssociate::stop()
	{
		_threadpool.stop();
		_timer.stop();
		_tcpServer.stop();
	}
	void spellingAssociate::onConnection(const meihao::TcpConnectionPtr& conn)
	{
		cout<<conn->toString()<<" has connected!"<<endl;
		conn->send("you has connected to the spellingAssociate server!");
	}
	void spellingAssociate::onMessage(const meihao::TcpConnectionPtr& conn)
	{
		string msg = conn->receive();  //接收一行
		cout<<msg<<endl;
		int pos = msg.find('\n');  //去掉换行符
		string queryWord = msg.substr(0,pos);
		cout<<queryWord;  //测试一下有没有去掉换行
		//对应的建立一个任务
		MyTask task(queryWord,conn->fd());  //传递接收到的fd过去，线程就可以和客户端交互了
		_threadpool.addTask(bind(&MyTask::execute,&task,_1));  //占位符_1最终是传递的执行任务线程的cache
	}
	void spellingAssociate::onClose(const meihao::TcpConnectionPtr& conn)
	{
		cout<<conn->toString()<<" has closed!"<<endl;
	}
};
