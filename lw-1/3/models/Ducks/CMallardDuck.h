#pragma once

#include "../Fly.cpp"
#include "../Quack.cpp"
#include "../Dance.cpp"
#include "Duck/CDuck.h"

class CMallardDuck : public CDuck
{
public:
	CMallardDuck()
		: CDuck(CreateFlyWithWings(), CreateQuack(), CreateWaltzDance())
	{
	}

	void Display() const override
	{
		std::cout << "Mallard duck" << std::endl;
	}
};