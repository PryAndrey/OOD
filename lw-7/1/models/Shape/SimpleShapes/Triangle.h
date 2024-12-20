#pragma once

#include "../IShape.h"
#include "Shape.h"

class Triangle : public Shape
{
public:
	constexpr static const char* type = "triangle";

	Triangle(const RectD& frame,
		std::shared_ptr<ILineStyle> outlineStyle,
		std::shared_ptr<IFillStyle> fillStyle)
		: Shape(frame, std::move(outlineStyle), std::move(fillStyle))
	{
	}

	void Draw(gfx::ICanvas& canvas) const final
	{
		std::shared_ptr<const ILineStyle> outlineStyle = GetOutlineStyle();
		std::shared_ptr<const IFillStyle> fillStyle = GetFillStyle();

		if (fillStyle->IsEnabled() && fillStyle->GetColor().has_value())
		{
			canvas.BeginFill(fillStyle->GetColor().value());
		}

		canvas.SetLineWidth(outlineStyle->GetWidth());
		if (outlineStyle->IsEnabled() && outlineStyle->GetColor().has_value())
		{
			canvas.SetLineColor(outlineStyle->GetColor().value());
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

		if (fillStyle->IsEnabled() && fillStyle->GetColor().has_value())
		{
			canvas.EndFill();
		}
	}
};
