#ifndef DecoyDuck
#define DecoyDuck

#include "CDecoyDuck.h"
#include "../Dance/CNoDance.cpp"
#include "../Fly/CFlyNoWay.cpp"
#include "../Quack/CMuteQuack.cpp"

void CDecoyDuck::Display()
{
	cout << "DecoyDuck" << endl;
}

CDecoyDuck::CDecoyDuck()
	: CDuck(std::make_unique<CFlyNoWay>(), std::make_unique<CMuteQuack>(), std::make_unique<CNoDance>())
{
}

#endif
