 ///
 /// @file    testMain.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-19 11:31:52
 ///
 
#include"MyConf.h"
#include"MyDict.h"
#include<iostream>
using namespace std;
int main()
{
	meihao::MyConf conf("/home/meihao/spellingAssociate/online/conf/sa.conf");
	conf.show();
	meihao::MyDict* dict = meihao::MyDict::getInstance();
	dict->init( (conf.getMap())["dict.txt"].c_str(),NULL ) ;
	//dict->show_dict();
	dict->write_index_table();
	return 0;
}
