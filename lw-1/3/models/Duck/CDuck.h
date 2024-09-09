#pragma once

#include <functional>
#include <iostream>
#include <memory>

using DanceBehavior = std::function<void()>;
using FlyBehavior = std::function<void()>;
using QuackBehavior = std::function<void()>;

class Duck
{
public:
	void SetDanceBehavior(const DanceBehavior& newDance)
	{
		m_danceBehavior = newDance;
	}

	void SetFlyBehavior(const FlyBehavior& newFly)
	{
		m_flyBehavior = newFly;
	}

	void PerformQuack()
	{
		m_quackBehavior();
	}

	void PerformDance()
	{
		m_danceBehavior();
	}

	void PerformFly()
	{
		m_flyBehavior();
	}

private:
	DanceBehavior m_danceBehavior;
	FlyBehavior m_flyBehavior;
	QuackBehavior m_quackBehavior;
};