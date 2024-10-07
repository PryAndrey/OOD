#pragma once

#include "../../../CPoint.h"
#include "../../CShape.h"

namespace shapes
{
class CCircleShapeType : public IShapeType
{
public:
	CCircleShapeType(double x, double y, double r);
	void Draw(gfx::ICanvas& canvas, const std::string& color) const override;
	void Move(double dx, double dy) override;
	[[nodiscard]] std::string GetStringType() const override;
	[[nodiscard]] std::string GetStringParams() const override;

private:
	CPoint m_coord;
	double m_r;
};

} // namespace shapes
