#ifndef Duck
#define Duck

#include "CDuck.h"
using namespace std;

CDuck::CDuck(std::unique_ptr<IFlyBehavior> flyBehavior,
	std::unique_ptr<IQuackBehavior> quackBehavior,
	std::unique_ptr<IDanceBehavior> danceBehavior)
	: m_flyBehavior(std::move(flyBehavior)),
	m_quackBehavior(std::move(quackBehavior)),
	m_danceBehavior(std::move(danceBehavior))
{
}

void CDuck::PerformQuack()
{
	if (m_quackBehavior)
	{
		m_quackBehavior->Quack();
	}
}

///  Принимать в конструкторе приватные поля - done
void CDuck::PerformFly()
{
	if (m_flyBehavior)
	{
		m_flyBehavior->Fly();
	}
}

void CDuck::PerformDance()
{
	if (m_danceBehavior)
	{
		m_danceBehavior->Dance();
	}
}

void CDuck::Swim()
{
	cout << "Swim" << endl;
}

///  Переименовать функцию - done
void CDuck::SetFlyBehavior(std::unique_ptr<IFlyBehavior> flyBehavior)
{
	m_flyBehavior = std::move(flyBehavior);
}
void CDuck::SetQuackBehavior(std::unique_ptr<IQuackBehavior> quackBehavior)
{
	m_quackBehavior = std::move(quackBehavior);
}
void CDuck::SetDanceBehavior(std::unique_ptr<IDanceBehavior> danceBehavior)
{
	m_danceBehavior = std::move(danceBehavior);
}

#endif