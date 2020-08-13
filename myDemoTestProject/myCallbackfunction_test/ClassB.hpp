#include"ClassA.hpp"
using namespace std;

class ClassB : public CCallback
{
public:
	ClassB()
	{
		m_ClassA = new ClassA(this);
	}

	void onCallbackFunc(int value, int type)
	{
		if (type == 0)
		{
			cout << "Typ_ZERO =  " << value << endl;
		}
		else
		{
			cout << "Typ_Other =  " << value << endl;
		}
	}
	void TestShowData()
	{
		m_ClassA->showValue();
	}
public:
	ClassA * m_ClassA;
};
