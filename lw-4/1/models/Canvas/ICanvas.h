#pragma once

#include <string>
#include "../CPoint.h"

namespace gfx
{

class ICanvas
{
public:
	virtual void SetColor(const std::string& color) = 0;

	virtual void DrawLine(CPoint from, CPoint to) = 0;

	virtual void DrawEllipse(double cx, double cy, double rx, double ry) = 0;

	virtual void Fill() = 0;

	virtual ~ICanvas() = default;
};

} // namespace gfx
