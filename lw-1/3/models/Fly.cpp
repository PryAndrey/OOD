#pragma once

#include <functional>
#include <iostream>

using namespace std;

auto CreateFlyWithWings = []() {
	return [flightCount = 0]() mutable {
		std::cout << "Shuh-Shuh!(wings) " << ++flightCount << std::endl;
	};
};

auto CreateFlyNoWay = []() {
	return []() {
		std::cout << ". . ." << std::endl;
	};
};