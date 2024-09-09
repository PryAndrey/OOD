#ifndef NoDance
#define NoDance

class CNoDance : public IDanceBehavior
{
	void Dance() override
	{
		cout << ". . ." << endl;
	};
};

#endif