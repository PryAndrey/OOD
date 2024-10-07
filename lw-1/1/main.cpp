#include "models/Ducks/CDecoyDuck.cpp"
#include "models/Ducks/CMallardDuck.cpp"
#include "models/Ducks/CRedHeadDuck.cpp"
#include "models/Ducks/CRubberDuck.cpp"

using namespace std;

int main()
{
	CMallardDuck mDuck;
	mDuck.Display();
	mDuck.PerformFly();
	mDuck.PerformQuack();
	mDuck.PerformDance();
	mDuck.Swim();
	cout << endl;

	CRedheadDuck rhDuck;
	rhDuck.Display();
	rhDuck.PerformFly();
	rhDuck.PerformFly();
	rhDuck.PerformFly();
	rhDuck.SetFlyBehavior(std::make_unique<CFlyNoWay>());
	rhDuck.PerformFly();
	rhDuck.SetFlyBehavior(std::make_unique<CFlyWithWings>());
	rhDuck.PerformFly();
	rhDuck.PerformFly();
	rhDuck.PerformFly();
	rhDuck.PerformFly();
	rhDuck.PerformQuack();
	rhDuck.PerformDance();
	rhDuck.Swim();
	cout << endl;

	CDecoyDuck dDuck;
	dDuck.Display();
	dDuck.PerformFly();
	dDuck.PerformQuack();
	dDuck.PerformDance();
	dDuck.Swim();
	cout << endl;

	CRubberDuck rDuck;
	rDuck.Display();
	rDuck.PerformFly();
	rDuck.PerformQuack();
	rDuck.PerformDance();
	rDuck.Swim();
	cout << endl;
}
