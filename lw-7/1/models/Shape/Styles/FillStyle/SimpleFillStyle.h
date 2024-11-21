#pragma once

#include <utility>

#include "../IStyle.h"
#include "IFillStyle.h"

class SimpleFillStyle : public IFillStyle
{
public:
	explicit SimpleFillStyle(std::optional<RGBAColor> color)
		: m_color(std::move(color))
	{
	}

	[[nodiscard]] std::optional<RGBAColor> GetColor() const override
	{
		return m_color;
	}

	void SetColor(RGBAColor color) override
	{
		m_color = color;
	}

private:
	std::optional<RGBAColor> m_color = std::nullopt;
};