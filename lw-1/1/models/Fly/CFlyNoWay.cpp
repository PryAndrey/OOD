#ifndef FlyNoWay
#define FlyNoWay

class CFlyNoWay : public IFlyBehavior
{
	void Fly() override {
		cout << ". . ." << endl;
	};
};

#endif