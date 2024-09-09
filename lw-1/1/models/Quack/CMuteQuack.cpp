#pragma once

class CMuteQuack : public IQuackBehavior
{
	void Quack() override
	{
		cout << ". . ." << endl;
	};
};
