#pragma once

#include "../IShape.h"
#include "Shape.h"

class Triangle : public Shape
{
public:
	constexpr static const char* type = "triangle";

	Triangle(const RectD& frame,
		std::unique_ptr<LineStyle> outlineStyle,
		std::unique_ptr<FillStyle> fillStyle)
		: Shape(frame, std::move(outlineStyle), std::move(fillStyle))
	{
	}

	void Draw(gfx::ICanvas& canvas) const final
	{
		const LineStyle& outlineStyle = GetOutlineStyle();
		const FillStyle& fillStyle = GetFillStyle();

		if (fillStyle.IsEnabled() && fillStyle.GetColor().has_value())
		{
			canvas.BeginFill(fillStyle.GetColor().value());
		}

		canvas.SetLineWidth(outlineStyle.GetWidth());
		if (outlineStyle.IsEnabled() && outlineStyle.GetColor().has_value())
		{
			canvas.SetLineColor(outlineStyle.GetColor().value());
		}
		else
		{
			canvas.SetLineColor({});
		}

		const auto [left, top, width, height] = GetFrame();

		const std::vector<std::pair<double, double>> vertices = {
			{ left + width / 2, top },
			{ left, top + height },
			{ left + width, top + height }
		};

		canvas.DrawPolygon(vertices);

		if (fillStyle.IsEnabled() && fillStyle.GetColor().has_value())
		{
			canvas.EndFill();
		}
	}
};
