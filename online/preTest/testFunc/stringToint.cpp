 ///
 /// @file    stringToint.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-23 15:11:19
 ///
 
#include<iostream>
#include<stdlib.h>
#include<string>
using namespace std;
int main()
{
	string str = "8848";
	unsigned short port = atoi(str.c_str());
	cout<<port<<endl;
	return 0;
}
