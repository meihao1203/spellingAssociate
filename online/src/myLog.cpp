///
/// @file    myLog.cpp
/// @author  meihao1203(meihao19931203@outlook.com)
/// @date    2018-05-27 15:15:06
///

#include"myLog.h"
#include<iostream>
using namespace std;
namespace meihao
{
	myLog* myLog::_plog = NULL;  //静态成员初始化
	/***********************实现(方便引用，就不单独放到一个文件中了)***********************/
	//构造函数
	myLog::myLog():rootCategory(log4cpp::Category::getRoot().getInstance("rootCategory"))
	{
		//获取根Category，引用成员必须在成员初始化列表初始化

		//根Category下添加子Category
		//		log4cpp::OstreamAppender* osAppender = new log4cpp::OstreamAppender("osAppender",&cout);
		//		log4cpp::PatternLayout* pLayout1 = new log4cpp::PatternLayout();
		//		pLayout1->setConversionPattern("%d: %p %c %x: %m%n");
		//		osAppender->setLayout(pLayout1);
		//		rootCategory.addAppender(osAppender);
		//		rootCategory.setPriority(log4cpp::Priority::DEBUG);

		//log文件会一直记录
		log4cpp::FileAppender*fileAppender = new log4cpp::FileAppender("fileAppender","/home/meihao/spellingAssociate/online/conf/log");
		log4cpp::PatternLayout* pLayout2 = new log4cpp::PatternLayout();
		pLayout2->setConversionPattern("%d: %p %c %x: %m%n");
		fileAppender->setLayout(pLayout2);
		rootCategory.addAppender(fileAppender);
		rootCategory.setPriority(log4cpp::Priority::DEBUG);

		//logrolling.log不超过指定大小，默认10M；这里我设置了5M,备份文件5个
		//如果想要用备份带回卷的日志文件记录方式，就把这里的注释去掉
		//	log4cpp::RollingFileAppender* rollingfileAppender = new log4cpp::RollingFileAppender(
		//			"rollingfileAppender","logrolling.log",5*1024,5);
		//	log4cpp::PatternLayout* pLayout3 = new log4cpp::PatternLayout();
		//	pLayout3->setConversionPattern("%d: %p %c %x: %m%n");
		//	rollingfileAppender->setLayout(pLayout3);
		//	rootCategory.addAppender(rollingfileAppender);
		//	rootCategory.setPriority(log4cpp::Priority::DEBUG);

		rootCategory.info("myLog()");
	}
};
