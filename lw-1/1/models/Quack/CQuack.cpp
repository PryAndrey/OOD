#pragma once

class CQuack : public IQuackBehavior
{
	void Quack() override{
		cout << "Kra-Kra!" << endl;
	};
};
