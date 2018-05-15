 ///
 /// @file    processDict.h
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-15 15:39:45
 ///
 
#ifndef __PROCESSDICT_H__
#define __PROCESSDICT_H__
#include<iostream>
#include<vector>
#include<map>
#include<string>
using namespace std;
namespace meihao
{
	class processDict
	{
		public:
			processDict(const string& path);
			void handleFile();
			void statisticWord();
			void writeAnswer();
			void showFile();  // 测试，看文件名有没有全部获取到
		private:
			string _path;  //语料存放路径
			vector<string> _fileName;  //语料文件里的所有txt文件名
			map<string,int> _staticMap;  //统计的单词，词频
			string _preFile;  //除去语料文件中的没用字符得到的文件
			string _dict;  //最终得到的词典
	};
};
#endif
