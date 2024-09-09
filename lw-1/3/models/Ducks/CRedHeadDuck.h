#pragma once

#include "../Fly.cpp"
#include "../Quack.cpp"
#include "../Dance.cpp"
#include "Duck/CDuck.h"

class CRedheadDuck : public CDuck
{
public:
	CRedheadDuck()
		: CDuck(CreateFlyWithWings(), CreateQuack(), CreateMinuetDance())
	{
	}

	void Display() const override
	{
		std::cout << "Redhead duck" << std::endl;
	}
};