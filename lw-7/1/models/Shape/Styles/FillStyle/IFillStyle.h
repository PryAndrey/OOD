#pragma once

#include <utility>

#include "../IStyle.h"

class IFillStyle : public Style
{
public:
	[[nodiscard]] std::optional<RGBAColor> GetColor() const override = 0;
	void SetColor(RGBAColor color) override = 0;
};