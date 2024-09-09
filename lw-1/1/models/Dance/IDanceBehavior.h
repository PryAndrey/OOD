#pragma once
#include <iostream>

struct IDanceBehavior
{
	virtual void Dance() = 0;
	virtual ~IDanceBehavior() = default;
};