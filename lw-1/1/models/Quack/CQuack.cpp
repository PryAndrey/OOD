#ifndef H_Quack
#define H_Quack

class CQuack : public IQuackBehavior
{
	void Quack() override
	{
		cout << "Quack!" << endl;
	};
};

#endif