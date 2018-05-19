 ///
 /// @file    MyDict.h
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-19 11:37:30
 ///
 
#ifndef __MYDICT_H__
#define __MYDICT_H
#include<iostream>
#include<map>
#include<vector>
#include<string>
using namespace std;
namespace meihao
{
	class MyDict  //每个线程都要去获取词典，为了防止创建多个词典对象，使用单例类模式
	{
		public:
			static MyDict* getInstance();
			void init(const char* dictpath,const char* cnDictpath);  //所有词典文件读入内存,并建立索引
			void show_dict();
			void show_index_table();
			MyDict();
			read_from(const char* dictPath);  // 读入词典文件
			void record_to_index(int idx);  // 建立索引，每个词典中的单词开始遍历


		private:
			static MyDict* _pInstance;
			vector<pair<string,int>> _dict;
			map<string,set<int> > _index_table;
	};
};
#endif
