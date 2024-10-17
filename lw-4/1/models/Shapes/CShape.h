#ifndef CSHAPE_H
#define CSHAPE_H

#include "../Canvas/ICanvas.h"
#include <memory>
#include <string>

namespace shapes {

    class CShape {
    public:
        CShape(std::string color);
        [[nodiscard]] std::string GetColor() const;
        [[nodiscard]] virtual std::string GetType() const = 0;
        [[nodiscard]] virtual std::string GetStringParams() const = 0;
        //просто ссылку
        virtual void Draw(std::unique_ptr<gfx::ICanvas> &canvas) const = 0;
        virtual ~CShape() = default;//?

    protected:
        std::string m_color;
    };
// yfgbcfnm rjl
} // namespace shapes

#endif // CSHAPE_H