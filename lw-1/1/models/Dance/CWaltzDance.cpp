#ifndef Waltz
#define Waltz

class CWaltzDance : public IDanceBehavior
{
	void Dance() override {
		cout << "Dance waltz" << endl;
	};
};

#endif