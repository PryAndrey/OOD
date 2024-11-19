#pragma once

#include "../IShape.h"

class Shape : public IShape
{
public:
	Shape(const RectD& frame,
		std::unique_ptr<LineStyle> outlineStyle,
		std::unique_ptr<FillStyle> fillStyle)
		: m_frame(frame)
		, m_outlineStyle(std::move(outlineStyle))
		, m_fillStyle(std::move(fillStyle))
	{
	}

	[[nodiscard]] RectD GetFrame() const override
	{
		return m_frame;
	}

	void SetFrame(const RectD& rect) override
	{
		m_frame = rect;
	}

	LineStyle& GetOutlineStyle() override
	{
		return *m_outlineStyle;
	}

	[[nodiscard]] const LineStyle& GetOutlineStyle() const override
	{
		return *m_outlineStyle;
	}

	FillStyle& GetFillStyle() override
	{
		return *m_fillStyle;
	}

	[[nodiscard]] const FillStyle& GetFillStyle() const override
	{
		return *m_fillStyle;
	}

private:
	RectD m_frame{};
	std::unique_ptr<LineStyle> m_outlineStyle;
	std::unique_ptr<FillStyle> m_fillStyle;
};
