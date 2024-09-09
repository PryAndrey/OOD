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
{
	m_quackBehavior = std::make_unique<CSqueak>();
	m_flyBehavior = std::make_unique<CFlyNoWay>();
	m_danceBehavior = std::make_unique<CNoDance>();
}

#endif
