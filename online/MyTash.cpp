///
/// @file    MyTash.cpp
/// @author  meihao1203(meihao19931203@outlook.com)
/// @date    2018-05-22 17:03:06
///

#include"MyTask.h"
#include<iostream>
#include<unistd.h>
#include<iterator>
#include"MyDict.h"
using namespace std;
namespace meihao
{
	MyTask::MyTask(const string& queryWord,int peerfd):_queryWord(queryWord)
													   ,_peerfd(peerfd)
	{
	}
	void MyTask::execute(Cache& cache)
	{//MyTask执行函数
		string result = cache.query(_queryWord); //cache中查找要查询的词
		if(result!=string())  //如果找到
		{
			::write(_peerfd,result.c_str(),result.size());
			cout<<"feedback client"<<endl;
			return ;
		}

		//queryIndexTable();  //cache里面没有就要去索引表里面查找
		//计算编辑距离
		//response(cache);  //返回结果，并存入cache
	}
	void MyTask::queryIndexTable()
	{
		MyDict* md = MyDict::getInstance();
		if(NULL==md)
		{
			cout<<"MyTask::queryIndexTable"<<endl;
			return ;
		}
		map<string,set<int> > indexTable = md->get_index_table();
		string ch;
		for(int idx=0;idx!=_queryWord.size();++idx)
		{
			ch = _queryWord[idx];
			if( indexTable.count(ch) )
			{	
				cout<<"indexTable has character"<<ch<<endl;
				//statistic(indexTable[_queryWord[idx]]);
			}
		}
	}
	void MyTask::statistic(set<int>& iset)
	{
		MyDict* md = MyDict::getInstance();
		if(NULL==md)
		{
			cout<<"MyTask::statistic"<<endl;
			return ;
		}
		vector<pair<string,int> > dict = md->get_dict();
		set<int>::iterator it = iset.begin();
		for(;it!=iset.end();++it)
		{
			string source = dict[*it].first;  //得到索引中对应的单词
			int idist = distance(source);  //计算最小编辑距离
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
	//	return editDistance(_queryWorld,source);
	}
};
