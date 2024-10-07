#ifndef RedheadDuck
#define RedheadDuck

#include "CRedHeadDuck.h"
#include "../Dance/CMinuetDance.cpp"
#include "../Quack/CQuack.cpp"
#include "../Fly/CFlyWithWings.cpp"

void CRedheadDuck::Display()
{
	cout << "RedheadDuck" << endl;
}

CRedheadDuck::CRedheadDuck()
	: CDuck(std::make_unique<CFlyWithWings>(), std::make_unique<CQuack>(), std::make_unique<CMinuetDance>())
{
}

#endif
