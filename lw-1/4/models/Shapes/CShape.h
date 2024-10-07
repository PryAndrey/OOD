#ifndef CSHAPE_H
#define CSHAPE_H

#include "../Canvas/ICanvas.h"
#include "ShapesStrategy/IShapeType.h"
#include <memory>
#include <string>

namespace shapes
{

class CShape
{
public:
	CShape(std::string id, std::string color, std::unique_ptr<IShapeType> shapeType);
	void Draw(gfx::ICanvas& canvas) const;
	void Move(double dx, double dy);
	void SetColor(const std::string& color);
	void SetNewShapeType(std::unique_ptr<IShapeType> newShapeType);
	[[nodiscard]] std::string GetId() const;
	[[nodiscard]] std::string GetColor() const;
	[[nodiscard]] std::string GetType() const;
	[[nodiscard]] std::string GetStringParams() const;
	~CShape() = default;

private:
	std::string m_id;
	std::string m_color;
	std::unique_ptr<IShapeType> m_shapeType;
};

} // namespace shapes

#endif // CSHAPE_H