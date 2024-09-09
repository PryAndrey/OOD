#pragma once

#include "../CColor.h"
#include "../CPoint.h"
#include "../Interface/ISolidShape.h"
#include <complex>
#include <iostream>

class CTriangle : public ISolidShape
{
public:
	CTriangle(
		CPoint point1,
		CPoint point2,
		CPoint point3,
		CColor outlineColor,
		CColor fillColor)
		: m_point1(point1)
		, m_point2(point2)
		, m_point3(point3)
		, m_outlineColor(outlineColor)
		, m_fillColor(fillColor)
	{
	}

	double GetArea() override
	{
		double distance12 = Distance(m_point1, m_point2);
		double distance13 = Distance(m_point1, m_point3);
		double distance23 = Distance(m_point2, m_point3);
		double s = (distance12 + distance13 + distance23) / 2;
		return std::sqrt(s * (s - distance12) * (s - distance13) * (s - distance23));
	}

	double GetPerimeter() override
	{
		return Distance(m_point1, m_point2) + Distance(m_point1, m_point3) + Distance(m_point2, m_point3);
	}

	std::string ToString() override
	{
		std::stringstream ss;
		ss << std::fixed << std::setprecision(2)
		   << m_point1.x << " " << m_point1.y << " "
		   << m_point2.x << " " << m_point2.y << " "
		   << m_point3.x << " " << m_point3.y << " "
		   << GetArea() << " "
		   << GetPerimeter();
		std::string strX1, strY1, strX2, strY2, strX3, strY3, strArea, strPerimeter;
		ss >> strX1 >> strY1 >> strX2 >> strY2 >> strX3 >> strY3 >> strArea >> strPerimeter;

		return "Triangle: \n"
			   "Point1: (X: "
			+ strX1
			+ ", Y: " + strY1 + ")\n"
			+ "Point2: (X: "
			+ strX2
			+ ", Y: " + strY2 + ")\n"
			+ "Point3: (X: "
			+ strX3
			+ ", Y: " + strY3 + ")\n"
			+ "OutlineColor: " + m_outlineColor.ToString() + "\n"
			+ "FillColor: " + m_fillColor.ToString() + "\n"
			+ "Area: " + strArea + "\n"
			+ "Perimeter: " + strPerimeter + "\n";
	}

	CColor GetOutlineColor() override
	{
		return m_outlineColor;
	}
	CColor GetFillColor() override
	{
		return m_fillColor;
	}

	CPoint GetPoint1()
	{
		return m_point1;
	}
	CPoint GetPoint2()
	{
		return m_point2;
	}
	CPoint GetPoint3()
	{
		return m_point3;
	}

	void Draw(ICanvas* canvas) override
	{
		std::vector<CPoint> points;
		points.emplace_back(m_point1);
		points.emplace_back(m_point2);
		points.emplace_back(m_point3);
		canvas->DrawPolygon(points, m_outlineColor, m_fillColor);
	}

private:
	CPoint m_point1;
	CPoint m_point2;
	CPoint m_point3;
	CColor m_outlineColor;
	CColor m_fillColor;

	static double Distance(CPoint a, CPoint b)
	{
		double dx = a.x - b.x;
		double dy = a.y - b.y;
		return std::sqrt(dx * dx + dy * dy);
	}
};
