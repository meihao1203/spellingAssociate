///
/// @file    myLog.h
/// @author  meihao1203(meihao19931203@outlook.com)
/// @date    2017-12-25 15:03:32
///

#ifndef __MYLOG_H__
#define __MYLOG_H__
#include<iostream>
#include<log4cpp/Category.hh>
#include<log4cpp/Appender.hh>
#include<log4cpp/OstreamAppender.hh>
#include<log4cpp/FileAppender.hh>
#include<log4cpp/RollingFileAppender.hh>
#include<log4cpp/PatternLayout.hh>
#include<log4cpp/Priority.hh>
#include<string>
#include<sstream>
using namespace std;
//using namespace log4cpp;   //为了程序可读性好,下面都自己加上作用域限定
//单例类封装log4cpp
namespace meihao
{
	enum myPriority{EMERG,FATAL,ALERT,CRIT,ERROR,WARN,NOTICE,INFO,DEBUG};
	class myLog
	{
		public:
			static myLog* getInstance();   
			static void destroy();
			void setPriority(myPriority priority);   //myPriority 我把它定义为一种enum类型
			void fatal(const char* msg);
			void error(const char* msg);
			void warn(const char* msg);
			void info(const char* msg);
			void debug(const char* msg);
			static myLog* _plog;
			log4cpp::Category& rootCategory;
		private:
			myLog();
			~myLog();
	};
	inline myLog::~myLog()
	{
		rootCategory.info("~mylog()");
		rootCategory.shutdown();   
	}
	inline void myLog::destroy()
	{
		_plog->rootCategory.info("myLog destroy");   //静态函数内部没有隐士传递的this指针，所以必须要用_plog对象指针来调用
		delete _plog;   //delete的处理方式是：先调用析构函数，然后在释放空间；
		//所以可以在析构函数里再向日志里打印信息，然后再关掉rootCategory
	}
	inline myLog* myLog::getInstance()
	{
		if(NULL==_plog)
		{
			_plog = new myLog();
		}
		return _plog;
	}
	//类对象调用,重新设置rootCategory优先级
	inline void myLog::setPriority(myPriority priority)
	{
		switch(priority)
		{
			case FATAL:rootCategory.setPriority(log4cpp::Priority::FATAL);break;
			case ERROR:rootCategory.setPriority(log4cpp::Priority::ERROR);break;
			case WARN:rootCategory.setPriority(log4cpp::Priority::WARN);break;
			case INFO:rootCategory.setPriority(log4cpp::Priority::INFO);break;
			case DEBUG:rootCategory.setPriority(log4cpp::Priority::DEBUG);break;
			default:
					   rootCategory.setPriority(log4cpp::Priority::DEBUG);break;
		}
	}
	inline void myLog::error(const char* msg)
	{
		rootCategory.error(msg);
	}
	inline void myLog::warn(const char* msg)
	{
		rootCategory.warn(msg);
	}
	inline void myLog::info(const char* msg)
	{
		rootCategory.info(msg);
	}
	inline void myLog::debug(const char* msg)
	{
		rootCategory.debug(msg);
	}
	inline void myLog::fatal(const char* msg)
	{
		rootCategory.fatal(msg);
	}

	/***********************myLog类定义完毕***********************/
	/***********************定义一些宏，引用的时候直接展开，让myLog使用更方便***********************/
	//把要输出的消息拼接上文件名，所在函数名，所在行号;msg是const char*，所以最后用c_str()函数进行转换
	//__FILE__ __func__ __LINE 这几个宏定义是编译器识别的，__LINE__是int类型
	//分别是文件名，函数名，所在行号
	//防止在函数中调用，减少调用开销，声明成内联函数
	inline string int2string(int lineNumber)
	{
		ostringstream oss;
		oss<<lineNumber;
		return oss.str();
	}
#define catMsg(msg) string(msg).append(" {fileName:")\
	.append(__FILE__).append(" functionName:")\
	.append(__func__).append(" lineNumber:")\
	.append(int2string(__LINE__)).append("}").c_str()
};
#endif
