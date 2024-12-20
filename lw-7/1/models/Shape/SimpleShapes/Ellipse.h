#pragma once

#include "../IShape.h"
#include "../Styles/FillStyle/SimpleFillStyle.h"
#include "../Styles/LineStyle/SimpleLineStyle.h"
#include "Shape.h"

class Ellipse : public Shape
{
public:
	constexpr static const char* type = "ellipse";

	Ellipse(const RectD& frame,
		std::shared_ptr<ILineStyle> outlineStyle,
		std::shared_ptr<IFillStyle> fillStyle)
		: Shape(frame, std::move(outlineStyle), std::move(fillStyle))
	{
	}

	void Draw(gfx::ICanvas& canvas) const override
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
			canvas.SetLineColor(0xFFFFFFFF);
		}

		auto frame = GetFrame();
		double cx = frame.left + frame.width / 2;
		const double cy = frame.top + frame.height / 2;
		const double rx = frame.width / 2;
		const double ry = frame.height / 2;
		canvas.DrawEllipse(cx, cy, rx, ry);

		if (fillStyle->IsEnabled() && fillStyle->GetColor().has_value())
		{
			canvas.EndFill();
		}
	}
};
