 ///
 /// @file    main.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-16 17:03:15
 ///
 
#include<iostream>
#include"Index.h"
using namespace std;
int main()
{
	meihao::Index index("./../../doc/dict.txt");
	index.readDict();
	index.indexMap();
	cout<<"write:"<<endl;
	index.indexMapSave();
}
