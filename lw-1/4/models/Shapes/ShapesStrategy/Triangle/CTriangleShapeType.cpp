#include "CTriangleShapeType.h"
#include <sstream>

namespace shapes
{
CTriangleShapeType::CTriangleShapeType(double x1, double y1, double x2, double y2, double x3, double y3)
	: m_coord1(x1, y1)
	, m_coord2(x2, y2)
	, m_coord3(x3, y3)
{
}
void CTriangleShapeType::Draw(gfx::ICanvas& canvas, const std::string& color) const
{
	canvas.SetColor(color);
	canvas.MoveTo(m_coord1.x, m_coord1.y);
	canvas.LineTo(m_coord2.x, m_coord2.y);
	canvas.LineTo(m_coord3.x, m_coord3.y);
	canvas.LineTo(m_coord1.x, m_coord1.y);
	canvas.Fill();
}

void CTriangleShapeType::Move(double dx, double dy)
{
	m_coord1.x += dx;
	m_coord1.y += dy;
	m_coord2.x += dx;
	m_coord2.y += dy;
	m_coord3.x += dx;
	m_coord3.y += dy;
}

std::string CTriangleShapeType::GetStringType() const
{
	return "triangle";
}

std::string CTriangleShapeType::GetStringParams() const
{
	std::ostringstream tempOSS;
	tempOSS << m_coord1.x << " " << m_coord1.y << " " << m_coord2.x << " " << m_coord2.y << " " << m_coord3.x << " " << m_coord3.y;
	return tempOSS.str();
}
} // namespace shapes