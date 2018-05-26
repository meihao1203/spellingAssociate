 ///
 /// @file    main.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-26 09:53:05
 ///

#include"cnDict.h"
#include<iostream>
using namespace std;
int main()
{
	//meihao::cnDict cnd("./file1.txt");
	meihao::cnDict cnd("/home/meihao/spellingAssociate/offline/cnsource/file1.txt");
	//绝对路径
	//cnd.jiebaCut();
	//cnd.statisticWord();
	//cnd.writeAnswer();
	cnd.process();
	return 0;
}
