#pragma once

#include "../../../CPoint.h"
#include "../../CShape.h"

namespace shapes
{
class CRectangleShapeType : public IShapeType
{
public:
	CRectangleShapeType(double x, double y, double width, double height);
	void Draw(gfx::ICanvas& canvas, const std::string& color) const override;
	void Move(double dx, double dy) override;
	[[nodiscard]] std::string GetStringType() const override;
	[[nodiscard]] std::string GetStringParams() const override;

private:
	CPoint m_coord;
	double m_width, m_height;
};

} // namespace shapes