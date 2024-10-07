#pragma once

#include "../../../CPoint.h"
#include "../../CShape.h"

namespace shapes
{
class CTextShapeType : public IShapeType
{
public:
	CTextShapeType(double x, double y, double fontSize, std::string text);
	void Draw(gfx::ICanvas& canvas, const std::string& color) const override;
	void Move(double dx, double dy) override;
	[[nodiscard]] std::string GetStringType() const override;
	[[nodiscard]] std::string GetStringParams() const override;

private:
	CPoint m_coord;
	double m_fontSize;
	std::string m_text;
};

} // namespace shapes