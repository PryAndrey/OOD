#pragma once

class CWaltzDance : public IDanceBehavior
{
	void Dance() override{
		cout << "Dance waltz" << endl;
	};
};
