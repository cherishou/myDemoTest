// myCallbackfunction_test3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <functional>
using namespace std;

//1 "方向盘" 类接收外部的操作, 把消息传到 "车" 类中, 车类把消息传入到 "轮子" 类上
//(子类发消息给父类)

//2 "方向盘" 类接收外部的操作, 把消息传入到 "轮子" 类上
//(子类发消息给子类)

//方向盘类
class Steering
{
private:
	function<void(float)> m_steeringAction;
public:
	//设置回调函数
	void setWheelConnectWithCar(function<void(float)> steeringAction)
	{
		m_steeringAction = steeringAction;
	}

	//转动方向盘
	void turn(float angle)
	{
		cout << "Steering turn " << angle << " angle" << endl;

		m_steeringAction(angle);
	}

};
//轮子类
class  Wheel
{
public:
	//转动轮子方向
	void turn(float angle)
	{
		cout << "Wheel turn " << angle << " angle" << endl;
	}
};

//车类
class Car
{
public:
	//虽然方向盘在车里, 但是用户可以直接对它进行操作
	Steering m_steering;
	Wheel m_wheel;

	Car()
	{
		setCarConnectWithWheel();
	}
#if 1//1 "方向盘" 类接收外部的操作, 把消息传到 "车" 类中, 车类把消息传入到 "轮子" 类上
	//设置车和方向盘连接的函数
	void setCarConnectWithWheel()
	{
		std::function<void(float)> _fun = std::bind(&Car::steeringAction, this, std::placeholders::_1);
		m_steering.setWheelConnectWithCar(_fun);
	}

	//当转动方向盘时, 会调用该函数, 然后改函数让轮子转动相应的角度
	void steeringAction(float angle)
	{
		m_wheel.turn(angle);
	}
#else//2 "方向盘" 类接收外部的操作, 把消息传入到 "轮子" 类上
	//设置车和方向盘连接的函数
	void setCarConnectWithWheel()
	{
		std::function<void(float)> _fun = std::bind(&Wheel::turn, &m_wheel, std::placeholders::_1);
		m_steering.setWheelConnectWithCar(_fun);
	}
#endif




};

int _tmain(int argc, _TCHAR* argv[])
{
	Car _car;
	//让方向盘转动30度
	_car.m_steering.turn(30);
	return 0;
}

//int main()
//{
//    return 0;
//}

