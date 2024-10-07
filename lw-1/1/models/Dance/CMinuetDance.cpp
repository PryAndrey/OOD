#ifndef Minuet
#define Minuet

class CMinuetDance : public IDanceBehavior
{
	void Dance() override {
		cout << "Dance Minuet" << endl;
	};
};

#endif