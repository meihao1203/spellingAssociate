 ///
 /// @file    test.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-16 19:40:26
 ///
 
#include"Threadpool.h"
#include<iostream>
#include<unistd.h>
#include"Cache.h"
using namespace std;
void threadrun(meihao::Cache& cache)
{
	cout<<cache.query("mei")<<endl;
	cout<<cache.query("张")<<endl;
	cache.addElement("张","张三");
}
int main()
{
	meihao::MyConf myconf("/home/meihao/spellingAssociate/online/conf/sa.conf");
	meihao::Threadpool threadpool(4,10,myconf);  //4线程，10任务
	threadpool.start();
	int cnt = 10;
	while(cnt>0)
	{
		threadpool.addTask(threadrun);
		sleep(1);  //这里不睡眠，线程执行太快了，myTask种子是用系统时间，导致数据都一样
		cnt--;
	}
	threadpool.updateCache();
	threadpool.addTask(threadrun);
	threadpool.stop();
	return 0;
}
