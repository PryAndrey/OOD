#ifndef C_PICTURE_H
#define C_PICTURE_H

#include "../Shapes/CShape.cpp"
#include <map>

namespace shapes
{
    class CPicture
    {
    public:
        void AddShape(const std::string& id, std::unique_ptr<CShape> shape);
        void ChangeColor(const std::string& id, const std::string& color);
        void ChangeShape(const std::string& id, std::unique_ptr<IShapeType> newShapeType);
        void DeleteShape(const std::string& id);
        void MoveShape(const std::string& id, double dx, double dy);
        void DrawShape(const std::string& id, gfx::ICanvas& canvas) const;

		void MovePicture(double dx, double dy);
        void List() const;
        [[nodiscard]] std::string GetShapeById(const std::string& id) const;
        void DrawPicture(gfx::ICanvas& canvas) const;

    private:
        std::map<std::string, std::unique_ptr<CShape>> m_shapes;
    };

}

#endif // C_PICTURE_H