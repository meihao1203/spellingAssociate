 ///
 /// @file    doublearr.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-23 11:15:20
 ///
 
#include<iostream>
using namespace std;
//void fun(int (*p)[3],int len)
void fun(int p[][3],int len)
{
	for(int i=0;i<len;++i)
	{
		for(int j=0;j<3;j++)
			cout<<p[i][j]<<" ";
		cout<<endl;
	}
}
int main()
{
	int arr[3][3] = {{1,2,3},
		{4,5,6},
		{7,8,9}};
	fun(arr,3);
}
//1 2 3 
//4 5 6 
//7 8 9 
