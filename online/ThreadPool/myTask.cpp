 ///
 /// @file    myTask.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-17 15:18:58
 ///
 
#include"myTask.h"
#include<iostream>
#include<stdlib.h>
using namespace std;
namespace meihao
{
	void myTask::process()
	{
		srand(time(NULL));
		int num = rand()%100;
		cout<<"produce a num:"<<num<<endl;
	}
};
