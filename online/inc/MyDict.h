 ///
 /// @file    MyDict.h
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-19 11:37:30
 ///
 
#ifndef __MYDICT_H__
#define __MYDICT_H__
#include<iostream>
#include<map>
#include<vector>
#include<string>
#include<set>

using namespace std;
namespace meihao
{
	class MyDict  //每个线程都要去获取词典，为了防止创建多个词典对象，使用单例类模式
	{
		class AutoRelease;
		public:
			static MyDict* getInstance();
			static AutoRelease ar;  //利用嵌套类实现对象自动释放
			void init(const char* dictpath,const char* cnDictpath);  //所有词典文件读入内存,并建立索引
			void show_dict();
			void write_index_table();
			MyDict();
			void read_from(const char* dictPath);  // 读入词典文件
			void record_to_index(int idx);  // 建立索引，每个词典中的单词开始遍历
			vector<pair<string,int> >& get_dict();
			map<string,set<int> >& get_index_table();
		private:
			static MyDict* _pInstance;
			vector<pair<string,int> > _dict;  // 词典
			map<string,set<int> > _index_table;  // 索引
		private:
			class AutoRelease
			{
				public:
					AutoRelease(){}
					~AutoRelease();
			};
	};
};
#endif
