#pragma once

#include "../../../CPoint.h"
#include "../../CShape.h"

namespace shapes
{
class CTriangleShapeType : public IShapeType
{
public:
	CTriangleShapeType(double x1, double y1, double x2, double y2, double x3, double y3);
	void Draw(gfx::ICanvas& canvas, const std::string& color) const override;
	void Move(double dx, double dy) override;
	[[nodiscard]] std::string GetStringType() const override;
	[[nodiscard]] std::string GetStringParams() const override;

private:
	CPoint m_coord1, m_coord2, m_coord3;
};

} // namespace shapes