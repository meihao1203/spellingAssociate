 ///
 /// @file    utf-8.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-26 15:44:25
 ///
 
#include<iostream>
#include<string>
#include<stdio.h>
using namespace std;
int main()
{
	string ch = "中";
	const char* chr = ch.c_str();  //中占三个字节，转换成一个char类型的时候，后面的字节丢失了
	cout<<"sizeof 中 :"<<ch.size()<<endl;  //3
	int i = (*chr&0xF0);
	cout<<i<<endl;
	printf("%x\n",i);
}
//sizeof 中 :3
//224
//e0
