#pragma once

#include <functional>
#include <iostream>

using namespace std;

auto CreateWaltzDance = []() {
	return []() {
		std::cout << "Dance waltz!" << std::endl;
	};
};

auto CreateMinuetDance = []() {
	return []() {
		std::cout << "Dance Minuet!" << std::endl;
	};
};

auto CreateNoDance = []() {
	return []() {
		std::cout << ". . ." << std::endl;
	};
};