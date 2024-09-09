#pragma once

#include <functional>
#include <iostream>

using namespace std;

auto CreateQuack = []() {
	return []() {
		std::cout << "Quack!" << std::endl;
	};
};

auto CreateSqueak = []() {
	return []() {
		std::cout << "Pip-Pip!" << std::endl;
	};
};

auto CreateMuteQuack = []() {
	return []() {
		std::cout << ". . ." << std::endl;
	};
};