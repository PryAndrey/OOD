#ifndef Squeak
#define Squeak

class CSqueak : public IQuackBehavior
{
	void Quack() override{
		cout << "Pip-Pip!" << endl;
	};
};

#endif