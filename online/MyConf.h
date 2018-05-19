 ///
 /// @file    MyConf.h
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-19 10:50:04
 ///
 
#ifndef __MYCONF_H__
#define __MYCONF_H__
#include<iostream>
#include<string>
#include<map>
using namespace std;
namespace meihao
{
	class MyConf
	{
		public:
			MyConf(const string& path);
			void init();
			map<string,string>& getMap();
			void show();
		private:
			string _filepath;  //配置文件路径
			map<string,string> _map;  //存放配置文件路径
	};
};
#endif
