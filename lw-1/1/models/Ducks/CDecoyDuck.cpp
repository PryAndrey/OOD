#ifndef DecoyDuck
#define DecoyDuck

#include "CDecoyDuck.h"
#include "../Dance/CNoDance.cpp"
#include "../Quack/CMuteQuack.cpp"
#include "../Fly/CFlyNoWay.cpp"

void CDecoyDuck::Display()
{
	cout << "DecoyDuck" << endl;
}

CDecoyDuck::CDecoyDuck()
{
	m_quackBehavior = std::make_unique<CMuteQuack>();
	m_flyBehavior = std::make_unique<CFlyNoWay>();
	m_danceBehavior = std::make_unique<CNoDance>();
}

#endif
