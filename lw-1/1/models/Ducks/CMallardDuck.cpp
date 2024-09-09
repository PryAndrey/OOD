#ifndef MallardDuck
#define MallardDuck

#include "CMallardDuck.h"
#include "../Dance/CWaltzDance.cpp"
#include "../Quack/CQuack.cpp"
#include "../Fly/CFlyWithWings.cpp"

void CMallardDuck::Display()
{
	cout << "MallardDuck" << endl;
}

CMallardDuck::CMallardDuck()
{
	m_quackBehavior = std::make_unique<CQuack>();
	m_flyBehavior = std::make_unique<CFlyWithWings>();
	m_danceBehavior = std::make_unique<CWaltzDance>();
}

#endif
