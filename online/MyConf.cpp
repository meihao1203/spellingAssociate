 ///
 /// @file    MyConf.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-19 11:12:40
 ///
 
#include"MyConf.h"
#include<iostream>
#include<fstream>
#include<errno.h>
#include<stdlib.h>
#include<sstream>
#include<iterator>
#define handle_error(msg)\
	do{ perror(msg); exit(EXIT_FAILURE); }while(0);
using namespace std;
namespace meihao
{
	MyConf::MyConf(const string& path)
	{
		_filepath = path;
		init();
	}
	void MyConf::init()
	{
		ifstream ifs(_filepath.c_str());
		if(!ifs.good())
		{
			handle_error("open file fail!");
		}
		string tmp,key,value;
		while( getline(ifs,tmp) )
		{
			istringstream iss(tmp);
			iss>>key>>value;
			_map.insert(::make_pair(key,value));
		}
		ifs.close();
	}
	map<string,string>& MyConf::getMap()
	{
		return _map;
	}
	void MyConf::show()
	{
		cout<<"路径 "<<_filepath<<endl;
		map<string,string>::iterator mit = _map.begin();
		for(;mit!=_map.end();)
		{
			cout<<mit->first<<" "<<mit->second<<endl;
			++mit;
		}
	}
};
