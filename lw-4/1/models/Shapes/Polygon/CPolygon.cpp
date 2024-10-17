#include "CPolygon.h"
#include <cmath>
#include <sstream>
#include <utility>

namespace shapes
{
CPolygon::CPolygon(std::string color, double x, double y, double r, double vertexCount)
	: CShape(std::move(color))
	, m_coord(x, y)
	, m_r(r)
	, m_vertexCount(vertexCount)
{
	if (vertexCount < 3)
	{
		throw std::invalid_argument("vertexCount must be > 3");
	}

	double angleStep = 2 * M_PI / m_vertexCount;

	for (int i = 0; i < m_vertexCount; ++i)
	{
		double angle = i * angleStep;
		double xVertex = m_coord.x + m_r * cos(angle);
		double yVertex = m_coord.y + m_r * sin(angle);
		m_vertices.emplace_back(xVertex, yVertex);
	}
}

//
void CPolygon::Draw(std::unique_ptr<gfx::ICanvas>& canvas) const
{
	canvas->SetColor(m_color);
	for (int i = 1; i < m_vertexCount; ++i)
	{
		canvas->DrawLine(m_vertices[i - 1], m_vertices[i]);
	}
	canvas->DrawLine(m_vertices[m_vertexCount - 1], m_vertices[0]);
	canvas->Fill();
}

std::string CPolygon::GetType() const
{
	return "regularPolygon";
}

std::string CPolygon::GetStringParams() const
{
	std::ostringstream tempOSS;
	tempOSS << m_coord.x << " " << m_coord.y << " " << m_r << " " << m_vertexCount;
	return std::move(tempOSS).str();
}

size_t CPolygon::GetVertexCount() const
{
	return m_vertexCount;
}

CPoint CPolygon::GetCenter()
{
	return m_coord;
}

double CPolygon::GetRadius() const
{
	return m_r;
}
} // namespace shapes