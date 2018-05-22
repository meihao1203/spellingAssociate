 ///
 /// @file    Cache.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-19 16:30:46
 ///
 
#include"Cache.h"
#include<iostream>
#include<iterator>
#include<errno.h>
#include<stdlib.h>
#define handle_error(msg)\
	do{ perror(msg); exit(EXIT_FAILURE);}while(0);
using namespace std;
namespace meihao
{
	Cache::Cache()
	{}
	Cache::Cache(const Cache& rhs)
	{
		_hashMap = rhs._hashMap;
	}
	void Cache::addElement(const string& key,const string& value)
	{
		_hashMap.insert(::make_pair(key,value));
	}
	string Cache::query(const string& word)
	{
		auto it = _hashMap.find(word);
		if(it!=_hashMap.end())
		{
			return it->second;
		}
		return string();
	}
	void Cache::readFromFile(const string& filename)
	{
		ifstream ifs(filename.c_str());
		if(!ifs.good())
		{
			handle_error("Cache ifs fail");
		}
		string line;
		string key,value;
		while(getline(ifs,line))
		{
			istringstream iss(line);
			iss>>key>>value;
			_hashMap.insert(::make_pair(key,value));
		}
		ifs.close();
	}
	void Cache::writeToFile(const string& filename)
	{
		ofstream ofs(filename.c_str());
		if(!ofs.good())
		{
			handle_error("Cache ofs fail");
		}
		auto it = _hashMap.begin();
		for(;it!=_hashMap.end();++it)
		{
			ofs<<it->first<<"\t"<<it->second<<endl;
		}
		ofs.close();
	}
	void Cache::update(const Cache& rhs)
	{
		auto it = rhs._hashMap.begin();
		for(;it!=rhs._hashMap.end();++it)
		{
			_hashMap.insert(*it);
		}
	}
	int Cache::size()
	{
		return _hashMap.size();
	}
};
