 ///
 /// @file    Index.h
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-16 16:35:13
 ///
 
#ifndef __INDEX_H__
#define __INDEX_H__
#include<iostream>
#include<vector>
#include<map>
#include<set>
using namespace std;
namespace meihao
{
	class Index
	{
		public:
			Index(const string& path);  //传递dict.txt路径
	//	private:  // 内部处理函数，不提供对外接口
			void readDict();
			void indexMap();
			void indexMapSave();  // 建立好的索引存入文件
		private:
			vector<pair<string,int> > _readDict;  // dict.txt文件都是string int格式，
			// 这里全部按这个格式一行一行的读进来
			map<char,set<int> > _index;  // 每个字符，统计在dict.txt中出现的位置和行号
			// 行号就等于_readDict对应单词的下标
			string _path;
	};
};
#endif
