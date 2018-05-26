 //
 /// @file    testMain.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-19 11:31:52
 ///
 
/* 最开始测试MyConf类和MyDict类的 */
#include"MyConf.h"
#include"MyDict.h"
#include<iostream>
using namespace std;
int main()
{
	meihao::MyConf conf("/home/meihao/spellingAssociate/online/conf/sa.conf");
	conf.show();
	meihao::MyDict* dict = meihao::MyDict::getInstance();
	//dict->init( (conf.getMap())["dict.txt"].c_str(),NULL ) ;
	dict->init( (conf.getMap())["dict.txt"].c_str(),(conf.getMap()["cnDict.txt"].c_str())) ;  //最后加上了中文词典
	//dict->show_dict();
	dict->write_index_table();
	return 0;
}
//路径 /home/meihao/spellingAssociate/online/conf/sa.conf
//cache /home/meihao/spellingAssociate/online/conf/cache
//dict.txt /home/meihao/spellingAssociate/offline/doc/dict.txt
//ip 192.168.254.136
//port 8848
