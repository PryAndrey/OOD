#pragma once

#include <iostream>
#include "IShape.h"

class ISolidShape : public IShape
{
public:
	virtual CColor GetFillColor() = 0;

	virtual ~ISolidShape() = default;
};
