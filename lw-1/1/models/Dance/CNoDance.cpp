#pragma once

class CNoDance : public IDanceBehavior
{
	void Dance() override
	{
		cout << ". . ." << endl;
	};
};
