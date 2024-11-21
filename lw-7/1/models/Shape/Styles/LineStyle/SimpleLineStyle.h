#pragma once

#include <utility>

#include "../IStyle.h"
#include "ILineStyle.h"

class SimpleLineStyle : public ILineStyle
{
public:
	explicit SimpleLineStyle(std::optional<RGBAColor> color, std::optional<double> width)
		: m_color(std::move(color))
	{
		if (width != std::nullopt)
		{
			m_width = width.value();
		}
	}

	[[nodiscard]] std::optional<RGBAColor> GetColor() const override
	{
		return m_color;
	}

	void SetColor(RGBAColor color) override
	{
		m_color = color;
	}

	[[nodiscard]] double GetWidth() const override
	{
		return m_width;
	}

	void SetWidth(double width) override
	{
		m_width = width;
	}

private:
	std::optional<RGBAColor> m_color = std::nullopt;
	double m_width = 0;
};