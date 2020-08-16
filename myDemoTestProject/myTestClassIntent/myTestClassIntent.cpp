// myTestClassIntent.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


/*
#include <iostream>
using namespace std;

class Test
{
public:
	Test()
	{
		cout << "Test::Test()" << endl;
	}
private:
	int mc;
};

class Base
{
public:
	Base(int a)
	{
		ma = a;
		cout << "Base::base()" << endl;
	}
	~Base()
	{
		cout << "Base::~base()" << endl;
	}
private:
	int ma;
	Test t;
};

class Derive : public Base
{
public:
	Derive(int b) :Base(b)
	{
		mb = b;
		cout << "Derive::derive()" << endl;
	}
	~Derive()
	{
		cout << "Derive::~derive()" << endl;
	}
private:
	int mb;
};

int main()
{
	Derive d(2);

	return 0;
}

*/


#include <iostream>
#include <typeinfo>
using namespace std;

class Base
{
public:
	Base(int a = 1)
	{
		ma = a;
	}
	virtual void show()
	{
		cout << "base show 1" << endl;
	}
	void show(int b)
	{
		cout << "base show 2" << endl;
	}
private:
	int ma;
};
class Derive : public Base
{
public:
	Derive(int b = 2) :Base(b)
	{
		mb = b;
	}
	void show()
	{
		cout << "derive show 1" << endl;
	}

private:
	int mb;
};
int main()
{
	Base b;
	Derive d;
	Base* p = &d;
	cout << "base size:" << " " << sizeof(b) << endl;
	cout << "derive size:" << " " << sizeof(d) << endl;
	cout << "p type:" << " " << typeid(p).name() << endl;
	cout << "*p type:" << " " << typeid(*p).name() << endl;
	return 0;

}

