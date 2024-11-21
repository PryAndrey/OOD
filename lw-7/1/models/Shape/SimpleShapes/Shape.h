#pragma once

#include <utility>

#include "../IShape.h"

class Shape : public IShape
{
public:
	Shape(const RectD& frame,
		std::shared_ptr<ILineStyle> outlineStyle,
		std::shared_ptr<IFillStyle> fillStyle)
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

	std::shared_ptr<ILineStyle> GetOutlineStyle() override
	{
		return m_outlineStyle;
	}

	[[nodiscard]] std::shared_ptr<const ILineStyle> GetOutlineStyle() const override
	{
		return m_outlineStyle;
	}

	std::shared_ptr<IFillStyle> GetFillStyle() override
	{
		return m_fillStyle;
	}

	[[nodiscard]] std::shared_ptr<const IFillStyle> GetFillStyle() const override
	{
		return m_fillStyle;
	}

private:
	RectD m_frame{};
	std::shared_ptr<ILineStyle> m_outlineStyle;
	std::shared_ptr<IFillStyle> m_fillStyle;
};
