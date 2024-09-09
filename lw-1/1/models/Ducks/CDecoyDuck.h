#pragma once

#include "Duck/CDuck.cpp"

class CDecoyDuck : public CDuck
{
public:
	CDecoyDuck();
	void Display() override;
};