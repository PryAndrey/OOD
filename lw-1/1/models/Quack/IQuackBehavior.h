#pragma once
#include <iostream>

struct IQuackBehavior
{
	virtual void Quack() = 0;
	virtual ~IQuackBehavior() = default;
};