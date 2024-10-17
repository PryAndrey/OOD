#pragma once
#include "CPicture.h"

namespace shapes {
    void CPicture::AddShape(std::shared_ptr<CShape> shape) {
        m_shapes.push_back(std::move(shape));
    }

    void CPicture::DeleteShape(size_t index) {
        if (index > m_shapes.size()) {
            throw std::invalid_argument("Wrong index");
        }
        m_shapes.erase(m_shapes.begin() + index);
    }

    void CPicture::DrawPicture(std::unique_ptr<gfx::ICanvas> &canvas) const {
        for (const auto &shape: m_shapes) {
            shape->Draw(canvas);
        }
    }

    [[nodiscard]] std::shared_ptr<CShape> CPicture::GetShape(size_t index) const {
        if (index > m_shapes.size()) {
            throw std::invalid_argument("Wrong index");
        }
        return m_shapes[index];
    }

    size_t CPicture::GetShapeCount() const {
        return m_shapes.size();
    }
} // namespace shapes
