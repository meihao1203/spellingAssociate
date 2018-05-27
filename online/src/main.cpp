 ///
 /// @file    main.cpp
 /// @author  meihao1203(meihao19931203@outlook.com)
 /// @date    2018-05-23 16:56:24
 ///
 
#include"spellingAssociate.h"
using namespace std;
int main()
{
	meihao::spellingAssociate sa("/home/meihao/spellingAssociate/online/conf/sa.conf");
	sa.start();
	return 0;
}
