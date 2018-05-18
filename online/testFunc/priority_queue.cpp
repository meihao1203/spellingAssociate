///
/// @file    priority_queue.cpp
/// @author  meihao1203(meihao19931203@outlook.com)
/// @date    2018-05-18 14:26:40
///

#include<queue>
#include<vector>
#include<iterator>
#include<iostream>
using namespace std;
class point
{
	public:
		point(int x=0,int y=0):_x(x),_y(y)
	{}
		//private:
	public:
		int _x;
		int _y;
		friend ostream& operator<<(ostream& os,const point& rhs);
};
ostream& operator<<(ostream& os,const point& rhs)
{
	os<<"("<<rhs._x<<","<<rhs._y<<")";
	return os;
}
class Compare
{
	public:
	bool operator()(const point& lhs,const point& rhs)
	{
		return (lhs._x*lhs._y)>(rhs._x*rhs._y);
	}
};
int main()
{
	point arr[4] = {point(1,3)
		,point(1,2)
			,point(3,4)
			,point(2,3)};
	priority_queue<point,vector<point>,Compare > myQue(arr,arr+4);
	while(!myQue.empty())
	{
		cout<<myQue.top()<<" ";
		myQue.pop();
	}
	cout<<endl;
	return 0;
}

