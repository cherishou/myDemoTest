// myCallbackfunction_test3.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <functional>
using namespace std;

//1 "������" ������ⲿ�Ĳ���, ����Ϣ���� "��" ����, �������Ϣ���뵽 "����" ����
//(���෢��Ϣ������)

//2 "������" ������ⲿ�Ĳ���, ����Ϣ���뵽 "����" ����
//(���෢��Ϣ������)

//��������
class Steering
{
private:
	function<void(float)> m_steeringAction;
public:
	//���ûص�����
	void setWheelConnectWithCar(function<void(float)> steeringAction)
	{
		m_steeringAction = steeringAction;
	}

	//ת��������
	void turn(float angle)
	{
		cout << "Steering turn " << angle << " angle" << endl;

		m_steeringAction(angle);
	}

};
//������
class  Wheel
{
public:
	//ת�����ӷ���
	void turn(float angle)
	{
		cout << "Wheel turn " << angle << " angle" << endl;
	}
};

//����
class Car
{
public:
	//��Ȼ�������ڳ���, �����û�����ֱ�Ӷ������в���
	Steering m_steering;
	Wheel m_wheel;

	Car()
	{
		setCarConnectWithWheel();
	}
#if 1//1 "������" ������ⲿ�Ĳ���, ����Ϣ���� "��" ����, �������Ϣ���뵽 "����" ����
	//���ó��ͷ��������ӵĺ���
	void setCarConnectWithWheel()
	{
		std::function<void(float)> _fun = std::bind(&Car::steeringAction, this, std::placeholders::_1);
		m_steering.setWheelConnectWithCar(_fun);
	}

	//��ת��������ʱ, ����øú���, Ȼ��ĺ���������ת����Ӧ�ĽǶ�
	void steeringAction(float angle)
	{
		m_wheel.turn(angle);
	}
#else//2 "������" ������ⲿ�Ĳ���, ����Ϣ���뵽 "����" ����
	//���ó��ͷ��������ӵĺ���
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
	//�÷�����ת��30��
	_car.m_steering.turn(30);
	return 0;
}

//int main()
//{
//    return 0;
//}

