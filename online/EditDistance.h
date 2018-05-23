 ///
 /// @file    EditDistance.h
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-23 10:00:35
 ///
 
#ifndef __EDITDISTANCE_H__
#define __EDITDISTANCE_H__
#include<iostream>
#include<string>
using namespace std;
namespace meihao
{
	class EditDistance
	{
		public:
			static int length(const string& str);  //计算字符串长度
			static int min(const int& a,const int& b,const int& c);
			static int editDistance(const string& source,const string& target);  // 源字符串变成目标字符串需要的编辑距离
			//void showEditMatrix(int (*editMatrix)[8],int i);
	};
};
#endif
