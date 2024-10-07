#include "CRectangleShapeType.h"
#include <sstream>

namespace shapes
{
CRectangleShapeType::CRectangleShapeType(double x, double y, double width, double height)
	: m_coord(x, y)
	, m_width(width)
	, m_height(height)
{
	if (width < 0)
	{
		throw std::invalid_argument("Width must be > 0");
	}
	if (height < 0)
	{
		throw std::invalid_argument("Height must be > 0");
	}
}

void CRectangleShapeType::Draw(gfx::ICanvas& canvas, const std::string& color) const
{
	canvas.SetColor(color);
	canvas.MoveTo(m_coord.x, m_coord.y);
	canvas.LineTo(m_coord.x + m_width, m_coord.y);
	canvas.LineTo(m_coord.x + m_width, m_coord.y + m_height);
	canvas.LineTo(m_coord.x, m_coord.y + m_height);
	canvas.LineTo(m_coord.x, m_coord.y);
	canvas.Fill();
}

void CRectangleShapeType::Move(double dx, double dy)
{
	m_coord.x += dx;
	m_coord.y += dy;
}

std::string CRectangleShapeType::GetStringType() const
{
	return "rectangle";
}

std::string CRectangleShapeType::GetStringParams() const
{
	std::ostringstream tempOSS;
	tempOSS << m_coord.x << " " << m_coord.y << " " << m_width << " " << m_height;
	return tempOSS.str();
}
} // namespace shapes