// myCallbackfunction_test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"ClassB.hpp"

int main()
{
	ClassB *m_classB = new ClassB();

	m_classB->TestShowData();

	system("pause:");
    return 0;
}

