// myCallBackFunction_test5.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <functional>



using std::cout;
using std::endl;



std::function<bool(int, int)> fun;

class CEvent {
public:
	virtual void hiReply() = 0;
};


class A   //假设这个类就是socket的服务端基类
{
public:
    virtual void classAFuntion()
    {
        cout << " this is class A of function" << endl;
    }
	void classAFuntion2()
	{
		cout << "this is class A of function2" << endl;
	}

	

};


class B   //这个是对特定字段解析的类，就是事件分发
{
public:
	void classBFuntion()
	{
		cout << " this is calss B of function" << endl;
	}

	bool compare_member(int a, int b)
	{
		return a > b;
	}

	bool stepToSelect(std::string  data) 
	{
		if (data == "sever")
		{
			cout << "data come from server" << endl;
		}
		else if( data == "client")
 		{
			cout << "data come from client" << endl;
		}
		return true;
	}

	std::string printdata;
};


class C: public B //这个是整合的类，因为同一个socket 服务端
{
public:
	void classCFuntion()
	{
		cout << " this is calss C of function" << endl;
	}
};


int main()
{

	B testB;
	fun = std::bind(&B::compare_member, testB, std::placeholders::_1, std::placeholders::_2);
	bool result = fun(10, 1);
	


	C *testC = new C();
	testC->classBFuntion();




    std::cout << "Hello World!\n";
}


