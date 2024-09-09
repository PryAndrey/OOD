#pragma once
#include <iostream>

struct IFlyBehavior
{
	virtual void Fly() = 0;
	virtual ~IFlyBehavior() = default;
};