#pragma once

#include <string>
namespace gfx
{

class ICanvas
{
public:
	virtual void SetColor(const std::string& color) = 0;

	virtual void MoveTo(double x, double y) = 0;

	virtual void LineTo(double x, double y) = 0;

	virtual void DrawEllipse(double cx, double cy, double rx, double ry) = 0;
	virtual void DrawText(double left, double top, double fontSize, const std::string& textValue) = 0;

	virtual void Fill() = 0;
	virtual ~ICanvas() = default;
};

} // namespace gfx
