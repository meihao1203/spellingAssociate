 ///
 /// @file    test.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-16 19:40:26
 ///
 
#include"MutexLock.h"
#include"Threadpool.h"
#include"myTask.h"
#include"Task.h"
#include<iostream>
#include<unistd.h>
using namespace std;
int main()
{
	meihao::Threadpool threadpool(4,10);  //4线程，10任务
	threadpool.start();
	meihao::Task* task = new meihao::myTask;
	int cnt = 10;
	while(cnt>0)
	{
		threadpool.addTask(task);
		sleep(1);  //这里不睡眠，线程执行太快了，myTask种子是用系统时间，导致数据都一样
		cnt--;
	}
	threadpool.stop();
	return 0;
}
//produce a num:13
//produce a num:62
//produce a num:46
//produce a num:96
//produce a num:93
//produce a num:8
//produce a num:93
//produce a num:69
//produce a num:93
//produce a num:32
