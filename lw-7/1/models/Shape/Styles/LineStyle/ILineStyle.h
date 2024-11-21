#pragma once

#include <utility>

#include "../IStyle.h"

class ILineStyle : public Style
{
public:
	[[nodiscard]] std::optional<RGBAColor> GetColor() const override = 0;
	void SetColor(RGBAColor color) override = 0;

	virtual void SetWidth(double width) = 0;
	[[nodiscard]] virtual double GetWidth() const = 0;
};