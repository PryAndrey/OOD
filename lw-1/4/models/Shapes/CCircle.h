#pragma once

#include "../CColor.h"
#include "../CPoint.h"
#include "../Interface/ISolidShape.h"
#include <complex>
#include <iostream>

class CCircle : public ISolidShape
{
public:
	CCircle(
		CPoint point,
		double radius,
		CColor outlineColor,
		CColor fillColor)
		: m_point(point)
		, m_radius(radius)
		, m_outlineColor(outlineColor)
		, m_fillColor(fillColor)
	{
	}

	double GetArea() override
	{
		return M_PI * m_radius * m_radius;
	}

	double GetPerimeter() override
	{
		return 2 * M_PI * m_radius;
	}

	std::string ToString() override
	{
		std::stringstream ss;
		ss << std::fixed << std::setprecision(2)
		   << m_point.x << " "
		   << m_point.y << " "
		   << m_radius << " "
		   << GetArea() << " "
		   << GetPerimeter();
		std::string strX, strY, strRadius, strArea, strPerimeter;
		ss >> strX >> strY >> strRadius >> strArea >> strPerimeter;

		return "Circle: \n"
			   "Point: (X: "
			+ strX
			+ ", Y: " + strY + ")\n"
			+ "Radius: "
			+ strRadius + "\n"
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
	CPoint GetPoint()
	{
		return m_point;
	}
	[[nodiscard]] double GetRadius() const
	{
		return m_radius;
	}

	void Draw(ICanvas* canvas) override
	{
		canvas->DrawCircle(
			CPoint(m_point.x - m_radius, m_point.y - m_radius),
			m_radius,
			m_outlineColor,
			m_fillColor);
	}

private:
	CPoint m_point;
	double m_radius;
	CColor m_outlineColor;
	CColor m_fillColor;
};
