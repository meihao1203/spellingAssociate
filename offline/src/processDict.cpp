///
/// @file    processDict.cpp
/// @author  meihao1203(meihao19931203@outlook.com)
/// @date    2018-05-15 15:46:56
///

#include"processDict.h"
#include<iostream>
#include<sys/types.h>
#include<dirent.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include<iterator>
using namespace std;
#define handle_error(msg)\
	do{\
		perror(msg);\
		exit(EXIT_FAILURE);\
	}while(0);
namespace meihao
{
	void readDirName(const string& _path,vector<string>& _fileName)
	{
		//获取指定路径下的所有语料文件名
		DIR* dir = opendir(_path.c_str());
		if(NULL==dir)
			handle_error("opendir");
		struct dirent* q;
		while( (q=readdir(dir))!=NULL )
		{
			if( strcmp(".",q->d_name)!=0&&strcmp("..",q->d_name)!=0 )
			{
				string tmp = _path+q->d_name;
				_fileName.push_back(tmp);
			}
		}
	}
	processDict::processDict(const string& path):_path(path)
	{
		_preFile = "preFile.txt";
		_dict = "dict.txt";
	//	_fileName.push_back(_path);  //这是测试单个文件的代码
		readDirName(_path,_fileName);  //传入的是目录
	}
	void processDict::handleFile()
	{
		ofstream ofs(_preFile.c_str());
		for(auto& elem:_fileName)
		{

			ifstream ifs(elem.c_str());
			string tmp;
			while( getline(ifs,tmp),!ifs.eof() )
			{//把语料文件每一行中的无用字符去掉
				int i=0,size=tmp.size();
				while(i<size)
				{
					if(tmp[i]>=65&&tmp[i]<=90)  //大写字母
					{
						tmp[i++] += 32;  // 变小写
					}
					else if( tmp[i]>=97&&tmp[i]<=122 )  //小写字母,不做处理
					{
						i++;
					}
					else
					{
						tmp[i++] = ' ';
					}
				}
				ofs<<tmp<<endl;
			}
			ifs.close();
		}
		ofs.close();
	}
	void processDict::statisticWord()
	{	
		ifstream ifs(_preFile.c_str());
		string tmp;
		map<string,int>::iterator mit ;
		while( ifs>>tmp,!ifs.eof() )
		{
			mit = _statisticMap.find(tmp);
			if(mit!=_statisticMap.end())
			{
				_statisticMap[tmp]++;  // 词频+1
			}
			else
			{
				_statisticMap.insert(::make_pair(tmp,1));
			}
		}
		ifs.close();
	}
	void processDict::writeAnswer()
	{
		ofstream ofs(_dict.c_str());
		for( auto& elem: _statisticMap )
		{
			ofs<<elem.first<<" "<<elem.second<<endl;
		}
	}
	void processDict::showFile()
	{
		for(auto& elem:_fileName)
			cout<<elem<<endl;
	}
	void processDict::process()
	{
		handleFile();
		statisticWord();
		writeAnswer();
	}
};
