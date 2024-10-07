#pragma once

#include "ICanvas.h"
#include <iostream>
namespace shapes
{

class IShapeType
{
public:
	virtual void Draw(gfx::ICanvas& canvas, const std::string& color) const = 0;
	virtual void Move(double dx, double dy) = 0;
	[[nodiscard]] virtual std::string GetStringType() const = 0;
	[[nodiscard]] virtual std::string GetStringParams() const = 0;
	virtual ~IShapeType() = default;
};

} // namespace shapes
