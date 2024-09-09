#pragma once

#include "../CPoint.h"
#include "../Interface/ISolidShape.h"
#include <iostream>

class CRectangle : public ISolidShape
{
public:
	CRectangle(
		CPoint point,
		double width,
		double height,
		CColor outlineColor,
		CColor fillColor)
		: m_topLeftPoint(point)
		, m_width(width)
		, m_height(height)
		, m_outlineColor(outlineColor)
		, m_fillColor(fillColor)
	{
	}
	double GetArea() override
	{
		return m_width * m_height;
	}

	double GetPerimeter() override
	{
		return 2 * (m_width + m_height);
	}

	std::string ToString() override
	{
		std::stringstream ss;
		ss << std::fixed << std::setprecision(2)
		   << m_topLeftPoint.x << " "
		   << m_topLeftPoint.y << " "
		   << m_width << " "
		   << m_height << " "
		   << GetArea() << " "
		   << GetPerimeter();
		std::string strX, strY, strWidth, strHeight, strArea, strPerimeter;
		ss >> strX >> strY >> strWidth >> strHeight >> strArea >> strPerimeter;
		return "Rectangle: \n"
			   "TopLeftPoint: "
			   "(X: "
			+ strX
			+ ", Y: " + strY + ")\n"
			+ "Width: " + strWidth + "\n"
			+ "Height: " + strHeight + "\n"
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
	[[maybe_unused]] CPoint GetTopLeftPoint()
	{
		return m_topLeftPoint;
	}
	[[nodiscard]] double GetWidth() const
	{
		return m_width;
	}
	[[nodiscard]] double GetHeight() const
	{
		return m_height;
	}

	void Draw(ICanvas* canvas) override
	{
		canvas->DrawRectangle(m_topLeftPoint, m_width, m_height, m_outlineColor, m_fillColor);
	}

private:
	CPoint m_topLeftPoint;
	double m_width;
	double m_height;
	CColor m_outlineColor;
	CColor m_fillColor;
};
