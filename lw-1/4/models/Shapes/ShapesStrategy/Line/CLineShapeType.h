#pragma once

#include "../../../CPoint.h"
#include "../../CShape.h"

namespace shapes
{
class CLineShapeType : public IShapeType
{
public:
	CLineShapeType(double x1, double y1, double x2, double y2);
	void Draw(gfx::ICanvas& canvas, const std::string& color) const override;
	void Move(double dx, double dy) override;
	[[nodiscard]] std::string GetStringType() const override;
	[[nodiscard]] std::string GetStringParams() const override;

private:
	CPoint m_coord1, m_coord2;
};
} // namespace shapes
