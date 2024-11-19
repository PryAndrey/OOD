#pragma once

#include <utility>

#include "IStyle.h"

class FillStyle : public IStyle
{
public:
	explicit FillStyle(std::optional<RGBAColor> color)
		: m_color(std::move(color))
	{
	}

	[[nodiscard]] std::optional<bool> IsEnabled() const override
	{
		return m_enabled;
	}

	void Enable(bool enable) override
	{
		m_enabled = enable;
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
	std::optional<bool> m_enabled = std::nullopt;
	std::optional<RGBAColor> m_color = std::nullopt;
};

class LineStyle : public FillStyle
{

public:
	explicit LineStyle(double width, std::optional<RGBAColor> color)
		: FillStyle(std::move(color))
		, m_width(width)
	{
	}

	[[nodiscard]] double GetWidth() const
	{
		return m_width;
	}

	void SetWidth(double width)
	{
		m_width = width;
	}

private:
	double m_width = 0;
};