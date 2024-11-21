#pragma once
#include "../CoreTypes.h"
#include "../IDrawable.h"
#include "Styles/FillStyle/IFillStyle.h"
#include "Styles/LineStyle/ILineStyle.h"
#include <memory>

class IShape : public IDrawable
{
public:
	[[nodiscard]] virtual RectD GetFrame() const = 0;
	virtual void SetFrame(const RectD& rect) = 0;

	virtual std::shared_ptr<ILineStyle> GetOutlineStyle() = 0;
	[[nodiscard]] virtual std::shared_ptr<const ILineStyle> GetOutlineStyle() const = 0;

	virtual std::shared_ptr<IFillStyle> GetFillStyle() = 0;
	[[nodiscard]] virtual std::shared_ptr<const IFillStyle> GetFillStyle() const = 0;

	virtual ~IShape() = default;
};
