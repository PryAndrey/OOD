#include "CTextShapeType.h"
#include <sstream>

namespace shapes
{
CTextShapeType::CTextShapeType(double x, double y, double fontSize, std::string text)
	: m_coord(x, y)
	, m_fontSize(fontSize)
	, m_text(std::move(text))
{
	if (fontSize < 0)
	{
		throw std::invalid_argument("FontSize must be > 0");
	}
}

void CTextShapeType::Draw(gfx::ICanvas& canvas, const std::string& color) const
{
	canvas.SetColor(color);
	canvas.DrawText(m_coord.x, m_coord.y, m_fontSize, m_text);
}

void CTextShapeType::Move(double dx, double dy)
{
	m_coord.x += dx;
	m_coord.y += dy;
}

std::string CTextShapeType::GetStringType() const
{
	return "text";
}

std::string CTextShapeType::GetStringParams() const
{
	std::ostringstream tempOSS;
	tempOSS << m_coord.x << " " << m_coord.y << " " << m_fontSize << " " << m_text;
	return tempOSS.str();
}
} // namespace shapes