#pragma once

#include "../CColor.h"
#include "../CPoint.h"
#include "../Interface/IShape.h"

#include <complex>
#include <iostream>

class CLineSegment : public IShape
{
public:
	CLineSegment(CPoint startPoint, CPoint endPoint, CColor outlineColor)
		: m_startPoint(startPoint)
		, m_endPoint(endPoint)
		, m_outlineColor(outlineColor)
	{
	}
	double GetArea() override
	{
		return 0;
	}

	double GetPerimeter() override
	{
		double xPow2 = std::pow(m_startPoint.x - m_endPoint.x, 2);
		double yPow2 = std::pow(m_startPoint.y - m_endPoint.y, 2);
		double distance = std::sqrt(xPow2 + yPow2);
		return distance;
	}

	std::string ToString() override
	{
		std::stringstream ss;
		ss << std::fixed << std::setprecision(2)
		   << m_startPoint.x << " " << m_startPoint.y << " "
		   << m_endPoint.x << " " << m_endPoint.y << " "
		   << GetPerimeter();
		std::string strX1, strY1, strX2, strY2, strPerimeter;
		ss >> strX1 >> strY1 >> strX2 >> strY2 >> strPerimeter;

		return "Line: \n"
			   "StartPoint: (X: "
			+ strX1 + ", Y: " + strY1 + ")\n"
										"EndPoint: (X: "
			+ strX2 + ", Y: " + strY2 + ")\n"
										"OutlineColor: "
			+ m_outlineColor.ToString()
			+ "Area: 0\n"
			+ "Perimeter: " + strPerimeter + "\n";
	}

	CColor GetOutlineColor() override
	{
		return m_outlineColor;
	}
	CPoint GetStartPoint()
	{
		return m_startPoint;
	}
	CPoint GetEndPoint()
	{
		return m_endPoint;
	}

	void Draw(ICanvas* canvas) override
	{
		canvas->DrawLine(m_startPoint, m_endPoint, m_outlineColor);
	}

private:
	CPoint m_startPoint;
	CPoint m_endPoint;
	CColor m_outlineColor;
};
