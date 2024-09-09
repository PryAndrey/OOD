#include "CDucks.cpp"

using namespace std;


DanceBehavior CreateDanceBehavior(const std::string& danceName)
{
	int danceCount = 0;
	return [danceName, danceCount]() mutable {
		std::cout << "Dancing " << danceName << "! Dance #" << ++danceCount << std::endl;
	};
}

FlyBehavior CreateFlyBehavior(const std::string& flyName)
{
	return [flyName, flightCount = 0]() mutable {
		std::cout << "Flying " << flyName << "! Flight #" << ++flightCount << std::endl;
	};
}

FlyBehavior CreateQuackBehavior(const std::string& quackName)
{
	return [quackName, flightCount = 0]() mutable {
		std::cout << "Flying " << quackName << "! Flight #" << ++flightCount << std::endl;
	};
}

int main() {
	Duck mallard;
	mallard.SetDanceBehavior(CreateDanceBehavior("Waltz"));
	mallard.SetFlyBehavior(CreateFlyBehavior("with wings"));
	mallard.PerformDance(); // Вывод: Dancing Waltz! Dance #1
	mallard.PerformFly(); // Вывод: Flying with wings! Flight #1
	mallard.PerformDance(); // Вывод: Dancing Waltz! Dance #2
	mallard.PerformFly(); // Вывод: Flying with wings! Flight #2

	Duck redhead;
	redhead.SetDanceBehavior(CreateDanceBehavior("Minuet"));
	redhead.SetFlyBehavior(CreateFlyBehavior("with wings"));
	redhead.PerformDance(); // Вывод: Dancing Minuet! Dance #1
	redhead.PerformFly(); // Вывод: Flying with wings! Flight #1

	redhead.SetFlyBehavior(CreateFlyBehavior("no way"));
	redhead.PerformFly(); // Вывод: Flying no way! Flight #1

	return 0;
}
