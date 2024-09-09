#pragma once

#include "../CColor.h"
#include "../CPoint.h"
#include <iostream>
#include <vector>

class ICanvas
{
public:
	virtual void DrawLine(CPoint from, CPoint to, CColor lineColor) = 0;
	virtual void DrawPolygon(std::vector<CPoint> points, CColor outlineColor, CColor fillColor) = 0;
	virtual void DrawRectangle(CPoint topLeftPoint, double width, double height, CColor outlineColor, CColor fillColor) = 0;
	virtual void DrawCircle(CPoint center, double radius, CColor outlineColor, CColor fillColor) = 0;
	virtual void Display() = 0;//what happened
};
