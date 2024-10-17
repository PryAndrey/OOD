#pragma once

#include <vector>
#include "../../CPoint.h"
#include "../CShape.h"

namespace shapes
{
class CPolygon : public CShape
{
public:
    CPolygon(std::string color, double x, double y, double r, double vertexCount);
    void Draw(std::unique_ptr<gfx::ICanvas> &canvas) const override;
    [[nodiscard]] std::string GetType() const override;
    [[nodiscard]] std::string GetStringParams() const override;

    size_t GetVertexCount() const;
    CPoint GetCenter();
    double GetRadius() const;

private:
	CPoint m_coord;
    size_t m_vertexCount;
    double m_r;
    std::vector<CPoint> m_vertices;
};
} // namespace shapes
