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
		 ifs.close();
	 }
	 void MyDict::record_to_index(int idx)
	 {
		 string word = _dict[idx].first;
		 string key;
		 for(int iidx=0;iidx!=word.size();++iidx)
		 {
		// 这里是最先只处理英文的
		//	 key = word[iidx];
		//	 _index_table[key].insert(idx);  //不能把直接写word[iidx],要先用一个key来保存
			char ch = word[iidx];  //先取出第一个字节，判断是英文或一个字节的中文
			//还是多个字节表示的一个中文
			if(ch&(1<<7))
			{
				if((ch&0xE0)==0xC0)  //两个字节
				{
					key = word.substr(iidx,2);
					++idx;  //往后多取了一个字节,要++
				}
				else if((ch&0xF0)==0xE0)  //三个字节
				{
					key = word.substr(iidx,3);
					iidx += 2;
				}
				else if((ch&0xF8)==0xF0)  //四个字节
				{
					key = word.substr(iidx,4);
					iidx += 3;
				}
				else if((ch&0xFC)==0xF8)  //五个字节
				{
					key = word.substr(iidx,5);
					iidx += 4;
				}
				else if((ch&0xFE)==0xFC)  //六个字节
				{
					key = word.substr(iidx,6);
					iidx += 5;
				}
			}
			else //英文或单字节的汉字
			{
				key = word.substr(iidx,1);
			}
			 _index_table[key].insert(idx);
		 }
	 }
	 void MyDict::init(const char* dictpath,const char* cnDictpath)
	 {
		 //读入词典文件
		 read_from(dictpath);
		 read_from(cnDictpath);
		 //建立索引
		 for(int idx=0;idx!=_dict.size();++idx)
		{
			record_to_index(idx);  //对字典中的每一行的每一个单词建立索引
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
