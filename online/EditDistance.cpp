 ///
 /// @file    editDistance.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-23 14:22:06
 ///
 
#include"EditDistance.h"
#include<iostream>
#include<string.h>
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
	//void showEditMatrix(int (*editMatrix)[8],int i);
	int  EditDistance::editDistance(const string& source,const string& target)
	{
#if 0
		//这个只是针对英文的
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
		//showEditMatrix( editMatrix,source_len+1 );
		return editMatrix[source_len][target_len];
#endif
		//针对中文和英文
		int source_len = length(source);
		//cout<<"source_len:"<<source_len<<endl;
		int target_len = length(target);
		int editMatrix[source_len+1][target_len+1];
		//int editMatrix[source_len+1][8];  //具体的单词测试
		bzero(editMatrix,sizeof(editMatrix));
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
		// 因为中文字符可能占多个字节，不一定每次都只是偏移1个字节
		int source_off = 0 ,target_off;
		string subsource,subtarget;  //根据汉字字节数获取正确的汉字UTF-8编码
		for(int idx=1;idx<=source_len;++idx)
		{
			//if(source_off==source_len) break;
			int sofflen = nbytes(source[source_off]);
			//cout<<"sofflen:"<<sofflen;
			subsource = source.substr(source_off,sofflen);
			//cout<<" subsource:"<<subsource<<endl<<endl;
			source_off += sofflen;  //取了多少个字节，下次就要偏移都少个字节
			idx += (sofflen-1);
			target_off = 0;
			for(int iidx=1;iidx<=target_len;++iidx)
			{
				//if(target_off==target_len) break;
				int tofflen = nbytes(target[target_off]);
				//cout<<"tofflen:"<<tofflen;
				subtarget = target.substr(target_off,tofflen);
				//cout<<" subtarget:"<<subtarget<<endl<<endl;
				target_off += tofflen;
				iidx += (tofflen-1);
				int fij = 0;  //f(i,j)
				if(subsource!=subtarget)
				{
					//cout<<subsource<<" "<<subtarget<<" not same"<<endl;
					fij = 1;
				}
				editMatrix[idx][iidx] = min( editMatrix[idx-sofflen][iidx]+1,
						                     editMatrix[idx][iidx-tofflen]+1,
						                     editMatrix[idx-sofflen][iidx-tofflen]+fij);
			}
		}
		//showEditMatrix(editMatrix,6);
		return editMatrix[source_len][target_len];
	}
	void showEditMatrix(int (*editMatrix)[8],int i)  //测试的时候用例字符串长8，所以我直接写了8,二维数组都这样传值
	{
		for(int ii=0;ii!=i;++ii)
		{
			for(int jj=0;jj!=8;++jj)
			{
				cout<<editMatrix[ii][jj]<<" ";
			}
			cout<<endl;
		}
	}
	//计算中文一个汉子所占的字节数，英文就是一个字节
//1字节 0xxxxxxx 
//2字节 110xxxxx 10xxxxxx 
//3字节 1110xxxx 10xxxxxx 10xxxxxx 
//4字节 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx 
//5字节 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 
//6字节 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 

	int EditDistance::nbytes(const char ch)
	{
		int bytecnts = 0;
		if(ch & (1<<7))  //最高位为1，说明大于一个字节
		{
			if( (ch&0xE0)==0xC0 )  // 111X XXXX -> 110X XXXX
			{
				bytecnts += 2;
			}
			else if( (ch&0xF0)==0xE0 ) //  1111 XXXX -> 111X XXXX
			{
				bytecnts += 3;
			}
			else if( (ch&0xF8)==0xF0 ) // 1111 1XXX -> 1111 0XXX
			{
				bytecnts +=4 ;
			}
			else if( (ch&0xFC)==0xF8 ) // 1111 11XX -> 1111 1000
			{
				bytecnts += 5;
			}
			else if( (ch&0xFE)==0xFC ) // 1111 111X -> 1111 110X
			{
				bytecnts += 6;
			}
		}
		else 
		{//汉字只占一个字节，或者是英文
			bytecnts += 1;
		}
		return bytecnts;
	}
};


//int main()
//{
//	//string source = "中国";  //中文测试用例，如果要改的话，显示数组的函数也要改
//	string source = "sailn";
//	string target = "failing";
//	//string target = "中国人";
//	cout<<source.size()<<" "<<target.size()<<endl;
//	meihao::EditDistance::editDistance(source,target);
//}
//0 1 2 3 4 5 6 7 
//1 1 2 3 4 5 6 7 
//2 2 1 2 3 4 5 6 
//3 3 2 1 2 3 4 5 
//4 4 3 2 1 2 3 4 
//5 5 4 3 2 2 2 3
