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
	void PerformQuack();
	void PerformDance();
	void PerformFly();
	void SetOtherWings(std::unique_ptr<IFlyBehavior> newFly);
	static void Swim();
	virtual void Display() = 0;
protected:
	std::unique_ptr<IQuackBehavior> m_quackBehavior;
	std::unique_ptr<IFlyBehavior> m_flyBehavior;
	std::unique_ptr<IDanceBehavior> m_danceBehavior;
};

#endif