#include<iostream>

using namespace std;

class CCallback
{
public:
	virtual void onCallbackFunc(int value, int type) = 0;
};

class ClassA
{
public:
	ClassA(CCallback *pCallbackFunc)
	{
		m_pCallBack = pCallbackFunc;
	}

	void showValue()
	{
		m_pCallBack->onCallbackFunc(15, 0);
		m_pCallBack->onCallbackFunc(17, 1);
	}
private:
	CCallback *m_pCallBack;

};