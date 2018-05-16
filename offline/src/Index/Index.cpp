 ///
 /// @file    Index.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-16 16:48:21
 ///
 
#include"Index.h"
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<sstream>
#include<string>
#include<iterator>
using namespace std;
namespace meihao
{
	Index::Index(const string& path):_path(path)
	{
	}
	void Index::readDict()
	{	
		ifstream ifs(_path.c_str());
		if(!ifs.good())
		{
			perror("ifs");
			exit(EXIT_FAILURE);
		}
		string tmp;
		string item;
		string freq;
		pair<string,int> itemTmp;
		while(getline(ifs,tmp),!ifs.eof())
		{
			istringstream iss(tmp);
			iss>>item;
			itemTmp.first = item;
			iss>>freq;
			itemTmp.second = atoi(freq.c_str());
			_readDict.push_back(itemTmp);
		}
	}
	void Index::indexMap()
	{
		int dictSize = _readDict.size();  // 词典一共多少个词条
		int word;  //每一个词条的单词
		int wordLen;  //每一个单词的长度
		int idx = 0;
		map<char,set<int> >::iterator mit;
		while(idx<dictSize)
		{
			int i = 0;
		}
	}
};
