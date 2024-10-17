#pragma once

class CPoint
{
public:
	explicit CPoint(double newX = 0, double newY = 0)
		: x(newX)
		, y(newY)
	{
	}
    bool operator==(const CPoint& other) const {
        return x == other.x && y == other.y;
    }
	double x;
	double y;
};
