 ///
 /// @file    editDistance.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-23 14:22:06
 ///
 
#include"EditDistance.h"
#include<iostream>
using namespace std;
namespace meihao
{
	int EditDistance::length(const string& str)
	{
		int len = 0;
		len = str.size();
		return len;
	}
	int  EditDistance::min(const int& a,const int& b,const int& c)
	{
		return a<b?(a<c?a:c):(b<c?b:c);
	}
	int  EditDistance::editDistance(const string& source,const string& target)
	{
		int source_len = length(source);
		int target_len = length(target);
		//int editMatrix[source_len+1][8];
		int editMatrix[source_len+1][target_len+1];   
		//矩阵两条边初始化
		for(int sidx=0;sidx<=source_len;++sidx)
		{
			editMatrix[sidx][0] = sidx;
		}
		for(int tidx=0;tidx<=target_len;++tidx)
		{
			editMatrix[0][tidx] = tidx;
		}
		//填矩阵内容
		for(int idx=1;idx<=source_len;++idx)
		{
			for(int iidx=1;iidx<=target_len;++iidx)
			{
				int fij;
				if(source[idx-1]==target[iidx-1])  //f(i,j)
				{
					fij = 0;
				}
				else 
				{
					fij = 1;
				}
				editMatrix[idx][iidx] = min( editMatrix[idx-1][iidx]+1,
						editMatrix[idx][iidx-1]+1,
						editMatrix[idx-1][iidx-1]+fij);
			}
		}
	//	showEditMatrix( editMatrix,source_len+1 );
		return editMatrix[source_len][target_len];
	}
//	void showEditMatrix(int (*editMatrix)[8],int i)  //测试的时候用例字符串长8，所以我直接写了8,二维数组都这样传值
//	{
//		for(int ii=0;ii!=i;++ii)
//		{
//			for(int jj=0;jj!=8;++jj)
//			{
//				cout<<editMatrix[ii][jj]<<" ";
//			}
//			cout<<endl;
//		}
//	}
};
//int main()
//{
//	string source = "sailn";
//	string target = "failing";
//	meihao::editDistance(source,target);
//}
//0 1 2 3 4 5 6 7 
//1 1 2 3 4 5 6 7 
//2 2 1 2 3 4 5 6 
//3 3 2 1 2 3 4 5 
//4 4 3 2 1 2 3 4 
//5 5 4 3 2 2 2 3
