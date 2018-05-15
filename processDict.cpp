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
				_fileName.push_back(string(q->d_name));
		}
	}
	processDict::processDict(const string& path):_path(path)
	{
		_preFile = "preFile.txt";
		_dict = "dict.txt";
		readDirName(_path,_fileName);
	}
	void processDict::handleFile()
	{

	}
	void processDict::statisticWord()
	{

	}
	void processDict::writeAnswer()
	{

	}
	void processDict::showFile()
	{
		for(auto& elem:_fileName)
			cout<<elem<<endl;
	}
};
