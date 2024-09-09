#pragma once

class CFlyNoWay : public IFlyBehavior
{
	void Fly() override {
		cout << ". . ." << endl;
	};
};
