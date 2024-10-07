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
	: CDuck(std::make_unique<CFlyWithWings>(), std::make_unique<CQuack>(), std::make_unique<CWaltzDance>())
{
}

#endif
