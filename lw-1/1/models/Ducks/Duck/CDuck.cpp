#pragma once

#include "CDuck.h"
using namespace std;

void CDuck::PerformQuack()
{
	m_quackBehavior->Quack();
}

void CDuck::PerformFly()
{
	m_flyBehavior->Fly();
}

void CDuck::PerformDance()
{
	m_danceBehavior->Dance();
}

void CDuck::Swim()
{
	cout << "Swim" << endl;
}

void CDuck::SetOtherWings(std::unique_ptr<IFlyBehavior> newFly)
{
	m_flyBehavior = std::move(newFly);
}
