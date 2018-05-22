 ///
 /// @file    Compare.h
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-22 16:29:55
 ///
 
#ifndef __COMPARE_H__
#define __COMPARE_H__
#include<iostream>
using namespace std;
namespace meihao
{
	struct MyResult
	{
		string _word;
		int _iFreq;
		int _iDist;
	};
	class Compare
	{
		public:
			bool operator()(const MyResult& lhs,const MyResult& rhs)
			{
				if(lhs._iDist>rhs._iDist)  //>返回true，最后排序是从小到大
					return true;
				else if(lhs._iDist == rhs._iDist&&lhs._iFreq<rhs._iFreq) //<,从大到小排序
					return true;
				else if( lhs._iDist==rhs._iDist&&lhs._iFreq==rhs._iFreq&&lhs._word>rhs._word )
					return true;
				else
					return false;
			}
	};
};
#endif
