 ///
 /// @file    main.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-22 10:30:16
 ///
 
#include"TimerThread.h"
#include<iostream>
using namespace std;
namespace meihao
{
	void produce()
	{
		srand(time(NULL));
		int num = rand()%100;
		cout<<"produce a num:"<<num<<endl;
	}
};
int main()
{
	meihao::TimerThread th(meihao::produce,5,3);
	th.start();
	while(1);
}
