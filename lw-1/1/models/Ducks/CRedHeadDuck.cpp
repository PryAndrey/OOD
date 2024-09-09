#pragma once

#include "CRedHeadDuck.h"
#include "../Dance/CMinuetDance.cpp"
#include "../Quack/CQuack.cpp"
#include "../Fly/CFlyWithWings.cpp"

void CRedheadDuck::Display()
{
	cout << "RedheadDuck" << endl;
}

CRedheadDuck::CRedheadDuck()
{
	m_quackBehavior = std::make_unique<CQuack>();
	m_flyBehavior = std::make_unique<CFlyWithWings>();
	m_danceBehavior = std::make_unique<CMinuetDance>();
}
