#pragma once

class CFlyWithWings : public IFlyBehavior
{
public:
	void Fly() override {
		m_flightCount++;
		cout << "Shuh-Shuh!(wings)" << m_flightCount << endl;
	}

private:
	int m_flightCount = 0;
};
