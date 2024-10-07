#include "CCircleShapeType.h"
#include <sstream>

namespace shapes
{
CCircleShapeType::CCircleShapeType(double x, double y, double r)
	: m_coord(x, y)
	, m_r(r)
{
	if (r <= 0)
	{
		throw std::invalid_argument("Radius must be > 0");
	}
}

void CCircleShapeType::Draw(gfx::ICanvas& canvas, const std::string& color) const
{
	canvas.SetColor(color);
	canvas.DrawEllipse(m_coord.x, m_coord.y, m_r, m_r);
}

void CCircleShapeType::Move(double dx, double dy)
{
	m_coord.x += dx;
	m_coord.y += dy;
}

std::string CCircleShapeType::GetStringType() const
{
	return "circle";
}

std::string CCircleShapeType::GetStringParams() const
{
	std::ostringstream tempOSS;
	tempOSS << m_coord.x << " " << m_coord.y << " " << m_r;
	return tempOSS.str();
}
} // namespace shapes