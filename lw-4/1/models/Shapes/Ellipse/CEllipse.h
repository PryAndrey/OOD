#pragma once

#include "../../CPoint.h"
#include "../CShape.h"

namespace shapes {
    class CEllipse : public CShape {
    public:
        CEllipse(std::string color, double x, double y, double hR, double vR);

        void Draw(std::unique_ptr<gfx::ICanvas> &canvas) const override;

        [[nodiscard]] std::string GetType() const override;

        [[nodiscard]] std::string GetStringParams() const override;

        double GetHorizontalRadius();

        CPoint GetCenter();

        double GetVerticalRadius();

    private:
        CPoint m_coord;
        double m_hR, m_vR;
    };

} // namespace shapes
