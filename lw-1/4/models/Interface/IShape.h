#pragma once

#include "../CColor.h"
#include "ICanvasDrawable.h"
#include <iostream>

class IShape : public ICanvasDrawable
{
public:
	virtual double GetArea() = 0;

	virtual double GetPerimeter() = 0;

	virtual std::string ToString() = 0;

	virtual CColor GetOutlineColor() = 0;

	virtual ~IShape() = default;
};
