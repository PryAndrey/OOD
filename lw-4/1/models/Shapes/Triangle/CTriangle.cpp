#include "CTriangle.h"
#include <sstream>
#include <utility>

namespace shapes {
    CTriangle::CTriangle(std::string color, double x1, double y1, double x2, double y2, double x3, double y3)
            : CShape(std::move(color)), m_coord1(x1, y1), m_coord2(x2, y2), m_coord3(x3, y3) {
    }

    void CTriangle::Draw(std::unique_ptr<gfx::ICanvas> &canvas) const {
        canvas->SetColor(m_color);
        canvas->DrawLine(m_coord1, m_coord2);
        canvas->DrawLine(m_coord2, m_coord3);
        canvas->DrawLine(m_coord3, m_coord1);
        canvas->Fill();
    }

    std::string CTriangle::GetType() const {
        return "triangle";
    }

    std::string CTriangle::GetStringParams() const {
        std::ostringstream tempOSS;
        tempOSS << m_coord1.x << " " << m_coord1.y << " " << m_coord2.x << " " << m_coord2.y << " " << m_coord3.x << " "
                << m_coord3.y;
        return tempOSS.str();
    }

    CPoint CTriangle::GetVertex1(){
        return m_coord1;
    }

    CPoint CTriangle::GetVertex2(){
        return m_coord2;
    }

    CPoint CTriangle::GetVertex3(){
        return m_coord3;
    }
} // namespace shapes