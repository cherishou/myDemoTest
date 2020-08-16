// myTestClassIntent2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//



#include "iostream"


class Duck {
public:
	Duck() {}
	~Duck() {}
	//定义一个虚函数display
	virtual void display() 
	{
		std::cout << " I am a Duck !" << std::endl;
	}
};

class RedHandDuck :public Duck {
public:
	RedHandDuck() {}
	~RedHandDuck() {}

	//重写display
	void display()
	{
		std::cout << " I am a RedHandDuck !" << std::endl;
	}
};

int main()
{
	RedHandDuck* duck1 = new RedHandDuck();
	Duck* duck2 = duck1;
	duck1->display();
	duck2->display();//调用的display（）方法是根据传入的对象决定的。这就实现了“一个接口，多种方法”。

	//Duck* duck2 = new Duck();
	//duck2->display();

	std::getchar();

	system("pause");
}

//由结果可以看到，由于虚函数的使用，Duck对象（可以理解为接口），调用的display（）方法是根据传入的对象决定的。这就实现了“一个接口，多种方法”。


//多态与非多态的实质区别就是函数地址是早绑定还是晚绑定。如果函数的调用，在编译器编译期间就可以确定函数的调用地址，并生产代码，
//是静态的，就是说地址是早绑定的。而如果函数调用的地址不能在编译器期间确定，需要在运行时才确定，这就属于晚绑定。
