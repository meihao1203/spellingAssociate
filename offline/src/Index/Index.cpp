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
		string word;  //每一个词条的单词
		int wordLen;  //每一个单词的长度
		int idx = 0;
		map<char,set<int> >::iterator mit;
		while(idx<dictSize)
		{
			word = _readDict[idx].first;
			wordLen = word.size();
			int i = 0;
			while(i<wordLen)  // 对一个词条的每个字符进行统计
			{
				mit = _index.find(word[i]);
				if( _index.end()==mit  )  //没找到
				{
					pair<char,set<int> > newPair;
					newPair.first = word[i];
					newPair.second.insert(idx);  // 第二个参数表示出现这个字符的单词在词典中的哪一行，
					// 通过这个idx可以直接去vector中找到这个单词和频率
					_index.insert(newPair);
					i++;
					continue;
				}
				(mit->second).insert(idx);
				i++;
			}
			idx++;  //一个单词记录完了，开始记录下一个单词
		}
	}
	void Index::indexMapSave()
	{
		ofstream ofs("index.bat");
		for(auto &elem:_index)
		{
			ofs<<elem.first<<" ";
			for(auto &elem2:elem.second)
			{
				ofs<<elem<<" ";
			}
			ofs<<endl;
		}
	}
};
