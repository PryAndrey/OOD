#pragma once

#include "../Shape/GroupShape.h"
#include "ISlide.h"

class Slide : public ISlide
{
public:
	explicit Slide(double width, double height, const std::shared_ptr<GroupShape>& shapes)
		: m_background(0xFFFFFFFF)
		, m_width(width)
		, m_height(height)
		, m_shapes(shapes)
	{
	}

	[[nodiscard]] double GetWidth() const override
	{
		return m_width;
	}

	[[nodiscard]] double GetHeight() const override
	{
		return m_height;
	}

	[[nodiscard]] IShapes& GetShapes() override
	{
		return *m_shapes;
	}

	void Draw(gfx::ICanvas& canvas) const override
	{
		std::vector<std::pair<double, double>> background = { { 0, 0 }, { m_width, 0 }, { m_width, m_height }, { 0, m_height } };
		canvas.BeginFill(m_background);
		canvas.DrawPolygon(background);
		canvas.EndFill();
		m_shapes->Draw(canvas);
	}

private:
	double m_width;
	double m_height;
	std::shared_ptr<GroupShape> m_shapes;
	RGBAColor m_background;
};
