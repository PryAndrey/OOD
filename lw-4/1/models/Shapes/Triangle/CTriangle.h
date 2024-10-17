#pragma once

#include "../../CPoint.h"
#include "../CShape.h"

namespace shapes
{
class CTriangle : public CShape
{
public:
	CTriangle(std::string color, double x1, double y1, double x2, double y2, double x3, double y3);

    void Draw(std::unique_ptr<gfx::ICanvas> &canvas) const override;
    [[nodiscard]] std::string GetType() const override;
    [[nodiscard]] std::string GetStringParams() const override;
    CPoint GetVertex1();
    CPoint GetVertex2();
    CPoint GetVertex3();

private:
	CPoint m_coord1, m_coord2, m_coord3;
};

} // namespace shapes