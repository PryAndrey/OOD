#pragma once

#include "../IShape.h"
#include "Shape.h"

class Rectangle : public Shape
{
public:
	constexpr static const char* type = "rectangle";

	Rectangle(
		const RectD& frame,
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

		auto [left, top, width, height] = GetFrame();

		const std::vector<std::pair<double, double>> vertices = {
			{ left, top },
			{ left + width, top },
			{ left + width, top + height },
			{ left, top + height }
		};
		canvas.DrawPolygon(vertices);

		if (fillStyle.IsEnabled() && fillStyle.GetColor().has_value())
		{
			canvas.EndFill();
		}
	}
};
