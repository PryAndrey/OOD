#pragma once
#include "../CoreTypes.h"
#include "../IDrawable.h"
#include "Style/Style.h"
#include <memory>

class IShape : public IDrawable
{
public:
	[[nodiscard]] virtual RectD GetFrame() const = 0;
	virtual void SetFrame(const RectD& rect) = 0;

	virtual LineStyle& GetOutlineStyle() = 0;
	[[nodiscard]] virtual const LineStyle& GetOutlineStyle() const = 0;

	virtual FillStyle& GetFillStyle() = 0;
	[[nodiscard]] virtual const FillStyle& GetFillStyle() const = 0;

	virtual ~IShape() = default;
};
