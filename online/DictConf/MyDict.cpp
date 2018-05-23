 ///
 /// @file    MyDict.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-19 14:41:45
 ///
 
#include"MyDict.h"
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<errno.h>
#include<sstream>
#include<iterator>
#define handle_error(msg)\
	do{ perror(msg); exit(EXIT_FAILURE);}while(0);
using namespace std;
namespace meihao
{
	 MyDict* MyDict::_pInstance = NULL;
	 MyDict* MyDict::getInstance()
	 {
		 if(_pInstance == NULL)
		 {
			 _pInstance = new MyDict();
		 }
		 return _pInstance;
	 }
	 void MyDict::read_from(const char* dictPath)
	 {
		 ifstream ifs(dictPath);
		 if(!ifs.good())
		 {
			handle_error("MyDict ifs fail");
		 }
		 string line;
		 string pairString;
		 int pairInt;
		 while(getline(ifs,line))
		 {
			 istringstream iss(line);
			 iss>>pairString>>pairInt;
			 _dict.push_back(::make_pair(pairString,pairInt));
		 }
	 }
	 void MyDict::record_to_index(int idx)
	 {
		 string word = _dict[idx].first;
		 string key;
		 for(int iidx=0;iidx!=word.size();++iidx)
		 {
			 key = word[iidx];
			 _index_table[key].insert(idx);  //不能把直接写word[iidx],要先用一个key来保存
		 }
	 }
	 void MyDict::init(const char* dictpath,const char* cnDictpath)
	 {
		 //读入词典文件
		 read_from(dictpath);
		 //read_from(cnDictpath);
		 //建立索引
		 for(int idx=0;idx!=_dict.size();++idx)
		{
			record_to_index(idx);
		}
	 }
	 void MyDict::show_dict()
	 {
		for(auto& elem:_dict)
		{
			cout<<elem.first<<"\t"<<elem.second<<endl;
		}
	 }
	 void MyDict::write_index_table()
	 {
		 ofstream ofs("/home/meihao/spellingAssociate/online/conf/index_table");
		 if(!ofs.good())
		 {
			 handle_error("MyDict ofs fail");
		 }
		 map<string,set<int> >::iterator mit = _index_table.begin();
		 for(;mit!=_index_table.end();)
		 {
			 ofs<<mit->first<<" ";
			 for(auto& elem:mit->second)
			 {
				 ofs<<elem<<" ";
			 }
			 ofs<<endl;
			 ++mit;
		 }
	 }
	 MyDict::MyDict()
	 {
	 }
	 vector<pair<string,int> >& MyDict::get_dict()
	 {
		 return _dict;
	 }
	 map<string,set<int> >& MyDict::get_index_table()
	 {
		 return _index_table;
	 }
};
