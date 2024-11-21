#pragma once
#include "../SimpleShapes/Ellipse.h"
#include "../SimpleShapes/Rectangle.h"
#include "../SimpleShapes/Triangle.h"
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
		const auto rect = ReadRect(iss);

		if (shapeType == Triangle::type)
		{
			return ShapeFactory::CreateTriangle(std::move(outlineStyle), std::move(fillStyle), rect);
		}
		else if (shapeType == Ellipse::type)
		{
			return ShapeFactory::CreateEllipse(std::move(outlineStyle), std::move(fillStyle), rect);
		}
		else if (shapeType == Rectangle::type)
		{
			return ShapeFactory::CreateRectangle(std::move(outlineStyle), std::move(fillStyle), rect);
		}

		throw std::invalid_argument("Unknown shape type");
	}

private:
	static std::shared_ptr<Triangle> CreateTriangle(
		std::shared_ptr<SimpleLineStyle> outlineStyle,
		std::shared_ptr<SimpleFillStyle> fillStyle,
		RectD rect)
	{
		return std::make_unique<Triangle>(rect, std::move(outlineStyle), std::move(fillStyle));
	}

	static std::shared_ptr<Ellipse> CreateEllipse(
		std::shared_ptr<SimpleLineStyle> outlineStyle,
		std::shared_ptr<SimpleFillStyle> fillStyle,
		RectD rect)
	{
		return std::make_unique<Ellipse>(rect, std::move(outlineStyle), std::move(fillStyle));
	}

	static std::shared_ptr<Rectangle> CreateRectangle(
		std::shared_ptr<SimpleLineStyle> outlineStyle,
		std::shared_ptr<SimpleFillStyle> fillStyle,
		RectD rect)
	{
		return std::make_unique<Rectangle>(rect, std::move(outlineStyle), std::move(fillStyle));
	}

	static std::shared_ptr<SimpleLineStyle> ReadLineStyle(std::istringstream& iss)
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
		if ((iss >> lineWidth))
		{
			auto style = std::make_shared<SimpleLineStyle>(color, lineWidth);
			style->Enable(true);
			return style;
		}
		auto style = std::make_shared<SimpleLineStyle>(color, 0);
		style->Enable(true);
		return style;
	}

	static std::shared_ptr<SimpleFillStyle> ReadFillStyle(std::istringstream& iss)
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

		auto style = std::make_shared<SimpleFillStyle>(color);
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
