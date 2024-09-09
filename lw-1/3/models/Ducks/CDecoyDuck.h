#pragma once

#include "../Fly.cpp"
#include "../Quack.cpp"
#include "../Dance.cpp"
#include "Duck/CDuck.h"

class CDecoyDuck : public CDuck
{
public:
	CDecoyDuck()
		: CDuck(CreateFlyNoWay(), CreateMuteQuack(), CreateNoDance())
	{
	}

	void Display() const override
	{
		std::cout << "Decoy duck" << std::endl;
	}
};