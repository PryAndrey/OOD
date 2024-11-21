#pragma once

#include "../Shape/Factory/IShapeFactory.h"
#include "../Shape/GroupShape.h"
#include "../Slide/Slide.h"
#include <sstream>

class SlideService
{
public:
	explicit SlideService(IShapeFactory& shapeFactory)
		: m_shapeFactory(shapeFactory)
	{
	}

	void CreateSlide(std::istream& inputData, double width, double height)
	{
		std::string line;
		std::shared_ptr<GroupShape> firstGroup = std::make_shared<GroupShape>(); // Для этого используем enable_shared_from_this
		std::vector<std::shared_ptr<GroupShape>> groups;
		groups.push_back(firstGroup);

		while (getline(inputData, line) && line != "!")
		{
			if (IsGrouped(line, groups) || line.empty())
			{
				continue;
			}
			if (IsGroupEdit(line, groups))
			{
				continue;
			}

			auto shape = m_shapeFactory.CreateShape(line);
			groups.back()->InsertShape(shape, groups.back()->GetShapesCount());
		}

		m_currentSlide = std::make_unique<Slide>(width, height, std::move(firstGroup));
	}

	void DrawSlide(gfx::ICanvas& canvas)
	{
		if (m_currentSlide != nullptr)
		{
			m_currentSlide->Draw(canvas);
		}
	}

	static bool IsGrouped(const std::string& line, std::vector<std::shared_ptr<GroupShape>>& groups)
	{
		if (line == GroupShape::typeStart)
		{
			auto newGroup = std::make_shared<GroupShape>();

			groups.push_back(newGroup);
			return true;
		}

		if (line == GroupShape::typeEnd)
		{
			if (groups.size() > 1)
			{
				auto newGroup = groups.back();
				groups.pop_back();
				if (newGroup->GetShapesCount() > 0)
				{
					groups.back()->InsertShape(std::static_pointer_cast<IShape>(newGroup), groups.back()->GetShapesCount());
				}
			}
			return true;
		}

		return false;
	}

	static bool IsGroupEdit(const std::string& line, std::vector<std::shared_ptr<GroupShape>>& groups)
	{
		std::istringstream iss(line);

		std::string commandType;
		iss >> commandType;

		if (commandType == "resizeFrame")
		{
			const auto rect = ReadRect(iss);
			if (!groups.empty())
			{
				groups.back()->GetShapeAtIndex(groups.back()->GetShapesCount()-1)->SetFrame(rect);
			}
			return true;
		}

		if (commandType == "setLineStyle" || commandType == "setFillColor")
		{
			double lineWidth;
			std::optional<RGBAColor> color = ReadColor(iss);
			if (!color)
			{
				return false;
			}
			if (commandType == "setLineStyle")
			{
				if (iss >> lineWidth)
				{
					if (!groups.empty())
					{
						std::shared_ptr<ILineStyle> lineStyle = groups.back().get()->GetOutlineStyle();
						lineStyle->SetWidth(lineWidth);
						lineStyle->SetColor(color.value());
					}
					return true;
				}

				if (!groups.empty())
				{
					std::shared_ptr<ILineStyle> lineStyle = groups.back().get()->GetOutlineStyle();
					lineStyle->SetColor(color.value());
				}
				return true;
			}
			if (commandType == "setFillColor")
			{
				if (!groups.empty())
				{
					std::shared_ptr<IFillStyle> fillStyle = groups.back().get()->GetFillStyle();
					fillStyle->SetColor(color.value());
				}
			}
			return true;
		}

		return false;
	}

private:
	IShapeFactory& m_shapeFactory;
	std::unique_ptr<ISlide> m_currentSlide;

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

	static std::optional<RGBAColor> ReadColor(std::istringstream& iss)
	{
		std::string colorStr;
		try
		{
			if (iss >> colorStr)
			{
				return gfx::ToColor(colorStr).ToNum();
			}
		}
		catch (std::exception& e)
		{
			return std::nullopt;
		}
		return std::nullopt;
	}
};
