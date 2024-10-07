#ifndef H_Duck
#define H_Duck

#include "../../Dance/IDanceBehavior.h"
#include "../../Fly/IFlyBehavior.h"
#include "../../Quack/IQuackBehavior.h"
#include <iostream>
#include <memory>

class CDuck
{
public:
	CDuck(std::unique_ptr<IFlyBehavior> flyBehavior,
		std::unique_ptr<IQuackBehavior> quackBehavior,
		std::unique_ptr<IDanceBehavior> danceBehavior);
	void PerformQuack();
	void PerformDance();
	void PerformFly();
	void SetFlyBehavior(std::unique_ptr<IFlyBehavior> flyBehavior);
	void SetQuackBehavior(std::unique_ptr<IQuackBehavior> quackBehavior);
	void SetDanceBehavior(std::unique_ptr<IDanceBehavior> danceBehavior);
	void Swim();
	virtual void Display() = 0;

private:
	std::unique_ptr<IQuackBehavior> m_quackBehavior;
	std::unique_ptr<IFlyBehavior> m_flyBehavior;
	std::unique_ptr<IDanceBehavior> m_danceBehavior;
};

#endif