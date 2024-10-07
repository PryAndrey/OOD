#include "models/Ducks/CDecoyDuck.h"
#include "models/Ducks/CMallardDuck.h"
#include "models/Ducks/CRedHeadDuck.h"
#include "models/Ducks/CRubberDuck.h"
#include "models/Fly.cpp"
#include "models/Quack.cpp"
#include "models/Dance.cpp"

using namespace std;

void DrawDuck(CDuck const& duck)
{
	duck.Display();
}

void PlayWithDuck(CDuck& duck)
{
	DrawDuck(duck);
	duck.PerformQuack();
	duck.PerformFly();
	duck.PerformDance();
	std::cout << std::endl;
}

int main() {
	cout << "-----------------" << endl;
	CMallardDuck mallard;
	PlayWithDuck(mallard);
	mallard.PerformFly();
	mallard.PerformFly();
	mallard.PerformFly();
	mallard.SetFlyBehavior(CreateFlyNoWay());
	mallard.PerformFly();
	cout << "-----------------" << endl;

		cout << "-----------------" << endl;
	CRedheadDuck redhead;
	PlayWithDuck(redhead);
	redhead.PerformFly();
	redhead.PerformFly();
	redhead.PerformFly();
	redhead.SetFlyBehavior(CreateFlyNoWay());
	redhead.PerformFly();
	cout << "-----------------" << endl;

		cout << "-----------------" << endl;
	CDecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck);
	decoyDuck.PerformFly();
	decoyDuck.PerformFly();
	decoyDuck.PerformFly();
	decoyDuck.SetFlyBehavior(CreateFlyNoWay());
	decoyDuck.PerformFly();
	cout << "-----------------" << endl;

		cout << "-----------------" << endl;
	CRubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);
	rubberDuck.PerformFly();
	rubberDuck.PerformFly();
	rubberDuck.PerformFly();
	rubberDuck.SetFlyBehavior(CreateFlyNoWay());
	rubberDuck.PerformFly();
	cout << "-----------------" << endl;

	return 0;
}
