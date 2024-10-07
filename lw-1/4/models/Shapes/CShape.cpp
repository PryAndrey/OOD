#include "CShape.h"

namespace shapes
{
CShape::CShape(std::string id, std::string color, std::unique_ptr<IShapeType> shapeType)
	: m_id(std::move(id))
	, m_color(std::move(color))
	, m_shapeType(std::move(shapeType))
{
}

void CShape::Draw(gfx::ICanvas& canvas) const
{
	m_shapeType->Draw(canvas, m_color);
}

void CShape::Move(double dx, double dy)
{
	m_shapeType->Move(dx, dy);
}

std::string CShape::GetId() const
{
	return m_id;
}

std::string CShape::GetColor() const
{
	return "#" + m_color;
}

void CShape::SetColor(const std::string& color)
{
	m_color = color;
}

std::string CShape::GetType() const
{
	return m_shapeType->GetStringType();
}

std::string CShape::GetStringParams() const
{
	return m_shapeType->GetStringParams();
}

void CShape::SetNewShapeType(std::unique_ptr<IShapeType> newShapeType)
{
	m_shapeType = std::move(newShapeType);
}
} // namespace shapes