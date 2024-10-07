#ifndef RubberDuck
#define RubberDuck

#include "CRubberDuck.h"
#include "../Dance/CNoDance.cpp"
#include "../Quack/CSqueak.cpp"
#include "../Fly/CFlyNoWay.cpp"

void CRubberDuck::Display()
{
	cout << "RubberDuck" << endl;
}

CRubberDuck::CRubberDuck()
	: CDuck(std::make_unique<CFlyNoWay>(), std::make_unique<CSqueak>(), std::make_unique<CNoDance>())
{
}

#endif
