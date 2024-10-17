#include "CEllipse.h"
#include <sstream>
#include <utility>

namespace shapes {

    CEllipse::CEllipse(std::string color, double x, double y, double hR, double vR)
            : CShape(std::move(color)), m_coord(x, y), m_hR(hR), m_vR(vR) {
        if (hR <= 0 || vR <= 0) {
            throw std::invalid_argument("Radius must be > 0");
        }
    };

    void CEllipse::Draw(std::unique_ptr<gfx::ICanvas> &canvas) const {
        canvas->SetColor(m_color);
        canvas->DrawEllipse(m_coord.x, m_coord.y, m_hR, m_vR);
    }

    std::string CEllipse::GetType() const {
        return "circle";
    }

    std::string CEllipse::GetStringParams() const {
        std::ostringstream tempOSS;
        tempOSS << m_coord.x << " " << m_coord.y << " " << m_hR << " " << m_vR;
        return tempOSS.str();
    }

    double CEllipse::GetHorizontalRadius(){
        return m_hR;
    }

    double CEllipse::GetVerticalRadius(){
        return m_vR;
    }

    CPoint CEllipse::GetCenter() {
        return m_coord;
    }

} // namespace shapes