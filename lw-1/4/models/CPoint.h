#pragma once

class CPoint
{
public:
	explicit CPoint(double newX = 0, double newY = 0)
		: x(newX)
		, y(newY)
	{
	}
	double x;
	double y;
};
