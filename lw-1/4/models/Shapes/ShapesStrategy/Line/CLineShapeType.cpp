#include "CLineShapeType.h"
#include <sstream>

namespace shapes
{
CLineShapeType::CLineShapeType(double x1, double y1, double x2, double y2)
	: m_coord1(x1, y1)
	, m_coord2(x2, y2)
{
}

void CLineShapeType::Draw(gfx::ICanvas& canvas, const std::string& color) const
{
	canvas.SetColor(color);
	canvas.MoveTo(m_coord1.x, m_coord1.y);
	canvas.LineTo(m_coord2.x, m_coord2.y);
	canvas.Fill();
}

void CLineShapeType::Move(double dx, double dy)
{
	m_coord1.x += dx;
	m_coord1.y += dy;
	m_coord2.x += dx;
	m_coord2.y += dy;
}

std::string CLineShapeType::GetStringType() const
{
	return "line";
}

std::string CLineShapeType::GetStringParams() const
{
	std::ostringstream tempOSS;
	tempOSS << m_coord1.x << " " << m_coord1.y << " " << m_coord2.x << " " << m_coord2.y;
	return std::move(tempOSS).str();
}
} // namespace shapes