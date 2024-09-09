#pragma once

#include "models/Duck/CDuck.cpp"

class CMallardDuck : public CDuck
{
public:
	CMallardDuck();
	void Display() override;
};

class CRubberDuck : public CDuck
{
public:
	CRubberDuck();
	void Display() override;
};

class CDecoyDuck : public CDuck
{
public:
	CDecoyDuck();
	void Display() override;
};

class CRedheadDuck : public CDuck
{
public:
	CRedheadDuck();
	void Display() override;
};
