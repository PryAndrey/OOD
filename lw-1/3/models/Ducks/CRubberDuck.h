#pragma once

#include "../Fly.cpp"
#include "../Quack.cpp"
#include "../Dance.cpp"
#include "Duck/CDuck.h"

class CRubberDuck : public CDuck
{
public:
	CRubberDuck()
		: CDuck(CreateFlyNoWay(), CreateSqueak(), CreateNoDance())
	{
	}

	void Display() const override
	{
		std::cout << "Rubber duck" << std::endl;
	}
};