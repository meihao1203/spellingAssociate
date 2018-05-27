///
/// @file    MyTask.cpp
/// @author  meihao1203(meihao19931203@outlook.com)
/// @date    2018-05-22 17:03:06
///

#include"MyTask.h"
#include<iostream>
#include<unistd.h>
#include<iterator>
#include"MyDict.h"
#include"EditDistance.h"
#include"Socket.h"
#include<sstream>
#include"myLog.h"
using namespace std;
namespace meihao
{
	static meihao:: myLog* MyTasklog  = meihao::myLog::getInstance();
	static stringstream ss;
	MyTask::MyTask(const string& queryWord,int peerfd):_queryWord(queryWord)
													   ,_peerfd(peerfd)
													   ,_peerAddr(Socket::getPeerAddr(_peerfd))
	{
	}
	void MyTask::execute(Cache& cache)  //真正的任务执行体
	{//MyTask执行函数
		string result = cache.query(_queryWord); //cache中查找要查询的词
		ss.str("");
		ss<<getPeerfdAddr()<<" query word :"<<_queryWord<<endl;
		MyTasklog->info(catMsg(ss.str()));
		if(result!=string())  //如果找到
		{
			::write(_peerfd,result.c_str(),result.size());
			//cout<<getPeerfdAddr()<<" find in cache , feedback client "<<result<<endl;
			ss.str("");
			ss<<getPeerfdAddr()<<" find in cache , feedback client "<<result<<endl;
			MyTasklog->info(catMsg(ss.str()));
			return ;
		}
		queryIndexTable();  //cache里面没有就要去索引表里面查找
		//计算编辑距离
		response(cache);  //返回结果，并存入cache
	}
	void MyTask::queryIndexTable()
	{
		MyDict* md = MyDict::getInstance();
		if(NULL==md)
		{
			ss.str("");
			ss<<"MyTask::queryIndexTable MyDict::getInstance"<<endl;
			MyTasklog->error(catMsg(ss.str()));
			return ;
		}
		map<string,set<int> > indexTable = md->get_index_table();
		string ch;
		// 只是处理英文
	//	for(int idx=0;idx!=_queryWord.size();++idx)
	//	{
	//		ch = _queryWord[idx];
	//		if( indexTable.count(ch) )
	//		{	
	//			//cout<<"indexTable has character"<<ch<<endl;
	//			statistic(indexTable[ch]);  //对索引字符在词典中出现过的单词进行编辑距离计算
	//		}
	//	}
		// 处理中英文索引
		for(int idx=0;idx!=_queryWord.size();)
		{
			int cnt = meihao::EditDistance::nbytes(_queryWord[idx]);
			ch = _queryWord.substr(idx,cnt);  //中文可能占据多个字节，要一次读完
			idx += cnt;
			if(  indexTable.count(ch) )
			{
				//cout<<"indexTable has character"<<ch<<endl;
				statistic(indexTable[ch]);
			}
		}
	}
	void MyTask::statistic(set<int>& iset)
	{
		MyDict* md = MyDict::getInstance();
		if(NULL==md)
		{
			//cout<<"MyTask::statistic"<<endl;
			ss.str("");
			ss<<"MyTask::statistic"<<endl;
			MyTasklog->error(catMsg(ss.str()));
			return ;
		}
		vector<pair<string,int> > dict = md->get_dict();
		set<int>::iterator it = iset.begin();
		for(;it!=iset.end();++it)
		{
			string source = dict[*it].first;  //得到索引中对应的单词
			int idist = distance(source);  //计算最小编辑距离
			//cout<<"idist:"<<idist<<endl;
			if(idist<3)
			{
				MyResult res;
				res._word = source;
				res._iFreq = dict[*it].second;
				res._iDist = idist;
				_resultQue.push(res);
			}
		}
	}
	int MyTask::distance(const string& source)
	{
		return meihao::EditDistance::editDistance(_queryWord,source);  //计算客户端输入的单词
		//	变成词典中有的单词要编辑的距离
	}
	void MyTask::response(Cache& cache)
	{
		if( _resultQue.empty() )  //如果没有在索引中找到待选结果
		{
			string result = "no answer!";
			ss.str("");
			ss<<"response to "<<getPeerfdAddr()<<" "<<result<<endl;
			MyTasklog->info(catMsg(ss.str()));
			int ret = ::write(_peerfd,result.c_str(),result.size());
			if(-1==ret)
			{
				ss.str("");
				ss<<"MyTask::response client write error"<<endl;
				MyTasklog->error(catMsg(ss.str()));
				return ;
			}
		}
		else
		{
			MyResult result = _resultQue.top();
			ss.str("");
			ss<<getPeerfdAddr()<<" find in index , answer is:"<<result._word<<endl;
			MyTasklog->info(catMsg(ss.str()));
			int ret = ::write(_peerfd,result._word.c_str(),result._word.size());
			if(-1==ret)
			{
				ss.str("");
				ss<<"MyTask::response result error"<<endl;
				MyTasklog->error(catMsg(ss.str()));
				return ;
			}
			cache.addElement(_queryWord,result._word);  //添加到cache
			//cout<<getPeerfdAddr()<<" response word "<<_queryWord<<" add in cache"<<endl;
		}
		//cout<<getPeerfdAddr()<<" find in index,feedback client"<<endl;
	}
	string MyTask::getPeerfdAddr()
	{
		ostringstream oss;
		oss<< _peerAddr.ip()<<":"<<_peerAddr.port();
		return oss.str();
	}
};
