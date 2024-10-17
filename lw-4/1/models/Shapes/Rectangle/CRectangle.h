#pragma once

#include "../../CPoint.h"
#include "../CShape.h"

namespace shapes
{
class CRectangle : public CShape
{
public:
	CRectangle(std::string color, double x, double y, double width, double height);

    void Draw(std::unique_ptr<gfx::ICanvas> &canvas) const override;
    [[nodiscard]] std::string GetType() const override;
    [[nodiscard]] std::string GetStringParams() const override;

    CPoint GetLeftTop();
    CPoint GetRightBottom();

private:
	CPoint m_coord;
	double m_width, m_height;
};

} // namespace shapes