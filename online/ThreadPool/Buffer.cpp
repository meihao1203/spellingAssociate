 ///
 /// @file    Buffer.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-17 09:14:54
 ///
 
#include"Buffer.h"
#include<iostream>
using namespace std;
namespace meihao
{
	Buffer::Buffer(int size):_queSize(size)
							,_mutex()
							,_notFull(_mutex)
							,_notEmpty(_mutex)
							,_flag(true)
	{
	}
	bool Buffer::full()
	{
		return _queSize == _que.size();
	}
	bool Buffer::empty()
	{
		return _que.size() == 0;
	}
	void Buffer::push(DataType elem)
	{
		_mutex.lock();
		//if(full())
		while( full() )  //防止异常唤醒
		{
			_notFull.wait();
		}
		_que.push(elem);
		_notEmpty.notify();
		_mutex.unlock();
	}
	DataType Buffer::pop()
	{
		_mutex.lock();
		//if( _flag&&empty() )  //如果线程池没有关闭，并且队列为空
		while( _flag&&empty() )
		{
			_notEmpty.wait();
		}
		if(_flag)  //如果线程池没关闭，正常取任务
		{
			DataType tmp = _que.front();
			_que.pop();
			_notFull.notify();
			_mutex.unlock();
			return tmp;
		}
		else 
		{// 线程池关闭，直接退出
			_mutex.unlock();
			return NULL;
		}
	}
	void Buffer::wakeupEmpty()
	{
		_flag = false;  //关闭缓冲区
		_notEmpty.notifyall();
	}
};
