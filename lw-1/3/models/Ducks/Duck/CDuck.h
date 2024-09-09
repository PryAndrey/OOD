#pragma once

#include <iostream>
#include <functional>
#include <memory>

using FlyBehavior = std::function<void()>;
using QuackBehavior = std::function<void()>;
using DanceBehavior = std::function<void()>;

class CDuck
{
public:
	CDuck(FlyBehavior flyFunc, QuackBehavior quackFunc, DanceBehavior danceFunc)
		: m_flyFunc(std::move(flyFunc))
		, m_quackFunc(std::move(quackFunc))
		, m_danceFunc(std::move(danceFunc))
	{
	}

	void PerformFly() { m_flyFunc(); }
	void PerformQuack() { m_quackFunc(); }
	void PerformDance() { m_danceFunc(); }
	static void Swim() { std::cout << "Swim!" << std::endl; };
	virtual void Display() const = 0;

	void SetFlyBehavior(FlyBehavior flyFunc) { m_flyFunc = std::move(flyFunc); }
	void SetQuackBehavior(QuackBehavior quackFunc) { m_quackFunc = std::move(quackFunc); }
	void SetDanceBehavior(DanceBehavior danceFunc) { m_danceFunc = std::move(danceFunc); }

private:
	FlyBehavior m_flyFunc;
	QuackBehavior m_quackFunc;
	DanceBehavior m_danceFunc;
};