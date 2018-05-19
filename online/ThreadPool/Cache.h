 ///
 /// @file    Cache.h
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-19 16:17:06
 ///
 
#ifndef __CACHE__H__
#define __CACHE_H__
#include<iostream>
#include<unordered_map>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;
namespace meihao
{
	class Cache
	{
		public:
			Cache();
			Cache(const Cache& rhs);
			void addElement(const string& key,const string& value);
			string query(const string& word);
			void readFromFile(const string& filename);  //从文件中读入Cache
			void writeToFile(const string& filename);  //Cache写回磁盘
			void update(const Cache& rhs);  //更新当前线程内存中的Cache
		private:
			unordered_map<string,string> _hashMap;
	};
};
#endif
