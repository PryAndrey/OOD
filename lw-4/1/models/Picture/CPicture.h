#ifndef C_PICTURE_H
#define C_PICTURE_H

#include "../Shapes/CShape.h"
#include <map>
#include <vector>

namespace shapes
{
    class CPicture
    {
    public:
        void AddShape(std::shared_ptr<CShape> shape);
        void DeleteShape(size_t index);

        [[nodiscard]] std::shared_ptr<CShape> GetShape(size_t index) const;
        [[nodiscard]] size_t GetShapeCount() const;
        void DrawPicture(std::unique_ptr<gfx::ICanvas>& canvas) const;

    private:
        std::vector<std::shared_ptr<CShape>> m_shapes;
    };

}

#endif // C_PICTURE_H