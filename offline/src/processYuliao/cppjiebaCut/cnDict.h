 ///
 /// @file    cnDict.h
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-26 08:55:12
 ///
 
#ifndef __CNDICT_H__
#define __CNDICT_H__
#include<iostream>
#include<map>
#include<string>
using namespace std;
namespace meihao
{
	class cnDict
	{
		public:
			cnDict(const string& path);
			void process();  
		private:
			void jiebaCut();  //使用开源cppjieba分词
			void statisticWord();  //统计：单词 词频
			void writeAnswer();  //结果写入cnDict.txt
		private:
			string _path;
			map<string,int> _statisticMap;
			string _preFile;  //预处理结果放到文件保存
			string _cnDict;  //最终结果放到cnDict.txt
	};
};
#endif
