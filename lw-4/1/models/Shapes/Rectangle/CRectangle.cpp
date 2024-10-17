#include "CRectangle.h"
#include <sstream>
#include <utility>

namespace shapes {
    CRectangle::CRectangle(std::string color, double x, double y, double width, double height)
            : CShape(std::move(color)), m_coord(x, y), m_width(width), m_height(height) {
        if (width < 0) {
            throw std::invalid_argument("Width must be > 0");
        }
        if (height < 0) {
            throw std::invalid_argument("Height must be > 0");
        }
    }

    void CRectangle::Draw(std::unique_ptr<gfx::ICanvas> &canvas) const {
        canvas->SetColor(m_color);
        canvas->DrawLine(m_coord, CPoint(m_coord.x + m_width, m_coord.y));
        canvas->DrawLine(CPoint(m_coord.x + m_width, m_coord.y), CPoint(m_coord.x + m_width, m_coord.y + m_height));
        canvas->DrawLine(CPoint(m_coord.x + m_width, m_coord.y + m_height), CPoint(m_coord.x, m_coord.y + m_height));
        canvas->DrawLine(CPoint(m_coord.x, m_coord.y + m_height), m_coord);
        canvas->Fill();
    }

    std::string CRectangle::GetType() const {
        return "rectangle";
    }

    std::string CRectangle::GetStringParams() const {
        std::ostringstream tempOSS;
        tempOSS << m_coord.x << " " << m_coord.y << " " << m_width << " " << m_height;
        return tempOSS.str();
    }

    CPoint CRectangle::GetLeftTop() {
        return m_coord;
    }

    CPoint CRectangle::GetRightBottom() {
        return CPoint(m_coord.x + m_width, m_coord.y + m_height);
    }

} // namespace shapes