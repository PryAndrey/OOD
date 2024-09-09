#ifndef MuteQuack
#define MuteQuack

class CMuteQuack : public IQuackBehavior
{
	void Quack() override
	{
		cout << ". . ." << endl;
	};
};

#endif