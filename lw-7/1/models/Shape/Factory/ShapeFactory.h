#pragma once
#include "../SimpleShapes/Ellipse.h"
#include "../SimpleShapes/Rectangle.h"
#include "../SimpleShapes/Triangle.h"
#include "../Style/Style.h"
#include "IShapeFactory.h"

class ShapeFactory : public IShapeFactory
{
public:
	std::shared_ptr<IShape> CreateShape(const std::string& description) override
	{
		std::istringstream iss(description);

		std::string shapeType;
		iss >> shapeType;

		auto outlineStyle = ReadLineStyle(iss);
		auto fillStyle = ReadFillStyle(iss);

		if (shapeType == Triangle::type)
		{
			return ShapeFactory::CreateTriangle(iss, std::move(outlineStyle), std::move(fillStyle));
		}
		else if (shapeType == Ellipse::type)
		{
			return ShapeFactory::CreateEllipse(iss, std::move(outlineStyle), std::move(fillStyle));
		}
		else if (shapeType == Rectangle::type)
		{
			return ShapeFactory::CreateRectangle(iss, std::move(outlineStyle), std::move(fillStyle));
		}

		throw std::invalid_argument("Unknown shape type");
	}

private:
	static std::shared_ptr<Triangle> CreateTriangle(
		std::istringstream& iss,
		std::unique_ptr<LineStyle> outlineStyle,
		std::unique_ptr<FillStyle> fillStyle)
	{
		const auto rect = ReadRect(iss);

		return std::make_unique<Triangle>(rect, std::move(outlineStyle), std::move(fillStyle));
	}

	static std::shared_ptr<Ellipse> CreateEllipse(
		std::istringstream& iss,
		std::unique_ptr<LineStyle> outlineStyle,
		std::unique_ptr<FillStyle> fillStyle)
	{
		const auto rect = ReadRect(iss);

		return std::make_unique<Ellipse>(rect, std::move(outlineStyle), std::move(fillStyle));
	}

	static std::shared_ptr<Rectangle> CreateRectangle(
		std::istringstream& iss,
		std::unique_ptr<LineStyle> outlineStyle,
		std::unique_ptr<FillStyle> fillStyle)
	{
		const auto rect = ReadRect(iss);

		return std::make_unique<Rectangle>(rect, std::move(outlineStyle), std::move(fillStyle));
	}

	static std::unique_ptr<LineStyle> ReadLineStyle(std::istringstream& iss)
	{
		std::string colorStr;
		double lineWidth;
		std::optional<RGBAColor> color = std::nullopt;
		try
		{
			if (iss >> colorStr)
			{
				color = gfx::ToColor(colorStr).ToNum();
			}
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		auto style = std::make_unique<LineStyle>((iss >> lineWidth) ? lineWidth : 0, color);
		style->Enable(true);

		return style;
	}

	static std::unique_ptr<FillStyle> ReadFillStyle(std::istringstream& iss)
	{
		std::string colorStr;
		std::optional<RGBAColor> color = std::nullopt;
		try
		{
			if (iss >> colorStr)
			{
				color = gfx::ToColor(colorStr).ToNum();
			}
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}

		auto style = std::make_unique<FillStyle>(color);
		style->Enable(true);

		return style;
	}

	static RectD ReadRect(std::istringstream& iss)
	{
		double left, top, width, height;

		if (!(iss >> left >> top >> width >> height))
		{
			throw std::invalid_argument("Invalid rect parameters");
		}

		if (width < 0 || height < 0)
		{
			throw std::invalid_argument("Invalid width or height type");
		}

		return { left, top, width, height };
	}
};
