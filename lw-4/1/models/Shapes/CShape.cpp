#include "CShape.h"

namespace shapes {
    CShape::CShape(std::string color)
            : m_color(std::move(color)) {
    }

    std::string CShape::GetColor() const {
        return "#" + m_color;
    }
} // namespace shapes