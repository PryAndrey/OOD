#pragma once

class CSqueak : public IQuackBehavior
{
	void Quack() override{
		cout << "Pip-Pip!" << endl;
	};
};
