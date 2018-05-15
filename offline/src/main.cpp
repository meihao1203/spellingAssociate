 ///
 /// @file    main.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-15 16:04:06
 ///
 
#include"processDict.h"
#include<iostream>
using namespace std;
int main()
{
	meihao::processDict pa("./../source/");
	//meihao::processDict pa("./file1.txt");
	pa.showFile();
	cout<<"start process ..."<<endl;
	pa.process();
	cout<<"end process !"<<endl;
}
