///
/// @file    cnDict.cpp
/// @author  meihao1203(meihao19931203@outlook.com)
/// @date    2018-05-26 09:04:17
///

#include"cnDict.h"
#include<unistd.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<cppjieba/Jieba.hpp>
using namespace std;
namespace meihao
{
	cnDict::cnDict(const string& path):_path(path)
	{
		_preFile = "prefile.txt";
		_cnDict = "cnDict.txt";
	}
	//判断是否是中文标点符号
	bool punctuation(string elem)
	{
		if(elem=="，"||elem=="。"||elem=="；"||elem=="、"||elem=="】"
				||elem=="【"||elem=="！"||elem=="："||elem=="”"||elem=="“"
				||elem=="——"||elem=="……"||elem=="《"||elem=="》"||elem=="-"
				||elem=="？"||elem=="\r"
				||elem=="（"||elem=="）") //中文语料我是从windows系统下放到linux下处理的，系统换行差别，windows \r\n ,linux \n
			return true;  //是标点符号返回true
		else if(elem.c_str()[0]>='0'&&elem.c_str()[0]<='9')
			return true;
		return false;
	}
	void cnDict::jiebaCut()
	{
		ifstream ifs(_path.c_str(),ios::in);
		if(!ifs.good())
		{
			cout<<"jiebaCut ifs fail!"<<endl;
		}
		ifs.seekg(0,std::ios::end);
		int fileLen = ifs.tellg();
		//cout<<"fileLen:"<<fileLen<<endl;
		ifs.seekg(0,std::ios::beg);
		vector<string> cutWords;
		char* line = new char[fileLen];
		//allFile.reserve(fileLen);
		//ifs.read(&*allFile.begin(),fileLen);
		ifs.read(line,fileLen);
		string allFile = line;
		//cout<<"allFile size:"<<allFile.size()<<endl;
		jieba.Cut(allFile,cutWords,true);
		ifs.close();
		ofstream ofs(_preFile.c_str());
		if(!ofs.good())
		{
			cout<<"jiebaCut ofs fail"<<endl;
		}
		for(auto& elem:cutWords)
		{
			if(!punctuation(elem))
				ofs<<elem<<" ";
		}
		ofs.close();
	}
	void cnDict::statisticWord()
	{
		ifstream ifs(_preFile.c_str());
		if(!ifs.good())
		{
			cout<<"statisticWord ifs fail"<<endl;
		}
		string line;
		string word;
		while(getline(ifs,line))
		{
			istringstream iss(line);
			while(iss>>word)
			{
				map<string,int>::iterator it = _statisticMap.find(word);
				if(it!=_statisticMap.end())
				{
					it->second++;
				}
				else
				{
					_statisticMap.insert(::make_pair(word,1));
				}
			}
		}
	}
	void cnDict::writeAnswer()
	{
		ofstream ofs(_cnDict.c_str(),ios::in|ios::out);
		if(!ofs.good())
		{
			cout<<"writeAnswer ofs fail"<<endl;
		}
		map<string,int>::iterator it = _statisticMap.begin();
		for(;it!=_statisticMap.end();++it)
		{
			ofs<<it->first<<'\t'<<it->second<<endl;
		}
		ofs.close();
	}
	void cnDict::process()
	{
		jiebaCut();
		statisticWord();
		writeAnswer();
	}
};
