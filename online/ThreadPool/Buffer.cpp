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
							,_notFull()
							,_notEmpty()
							,_flag(false)
	{
	}
};
