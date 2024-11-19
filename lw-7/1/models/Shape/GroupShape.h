#pragma once

#include "IShape.h"
#include "IShapes.h"
#include "Style/GroupStyle.h"
#include "Style/Style.h"
#include <unordered_map>

class IGroupShape : public IShape
	, public IShapes
{
public:
	virtual ~IGroupShape() = default;
};

class GroupShape : public IGroupShape
{
public:
	constexpr static const char* typeStart = "group_start";
	constexpr static const char* typeEnd = "group_end";

	RectD GetFrame() const override
	{
		double left = std::numeric_limits<double>::max();
		double top = std::numeric_limits<double>::max();
		double right = std::numeric_limits<double>::lowest();
		double bottom = std::numeric_limits<double>::lowest();

		for (const auto& pair : m_shapes)
		{
			RectD frame = pair.second->GetFrame();
			left = std::min(left, frame.left);
			top = std::min(top, frame.top);
			right = std::max(right, frame.left + frame.width);
			bottom = std::max(bottom, frame.top + frame.height);
		}

		return { left, top, right - left, bottom - top };
	}

	void SetFrame(const RectD& rect) override
	{
		auto [left, top, width, height] = GetFrame();
		const double scaleX = rect.width / width;
		const double scaleY = rect.height / height;

		for (const auto& pair : m_shapes)
		{
			const RectD shapeFrame = pair.second->GetFrame();
			const double newLeft = rect.left + (shapeFrame.left - left) * scaleX;
			const double newTop = rect.top + (shapeFrame.top - top) * scaleY;
			const double newWidth = shapeFrame.width * scaleX;
			const double newHeight = shapeFrame.height * scaleY;
			pair.second->SetFrame({ newLeft, newTop, newWidth, newHeight });
		}
	}

	LineStyle& GetOutlineStyle() override
	{
		auto style = GetShapeAtIndex(0)->GetOutlineStyle();
		for (size_t i = 1; i < GetShapesCount(); ++i)
		{
			auto shape = GetShapeAtIndex(i);
			if (style.GetColor() != shape->GetOutlineStyle().GetColor())
			{
				LineStyle temp(0, std::nullopt);
				return temp;
			}
		}
		return GetShapeAtIndex(0)->GetOutlineStyle();
	}

	const LineStyle& GetOutlineStyle() const override
	{
		auto style = GetShapeAtIndex(0)->GetOutlineStyle();
		for (size_t i = 1; i < GetShapesCount(); ++i)
		{
			auto shape = GetShapeAtIndex(i);
			if (style.GetColor() != shape->GetOutlineStyle().GetColor())
			{
				LineStyle temp(0, std::nullopt);
				return temp;
			}
		}
		return GetShapeAtIndex(0)->GetOutlineStyle();
	}

	FillStyle& GetFillStyle() override
	{
		auto style = GetShapeAtIndex(0)->GetFillStyle();
		for (size_t i = 1; i < GetShapesCount(); ++i)
		{
			auto shape = GetShapeAtIndex(i);
			if (style.GetColor() != shape->GetFillStyle().GetColor())
			{
				LineStyle temp(0, std::nullopt);
				return temp;
			}
		}
		return GetShapeAtIndex(0)->GetFillStyle();
	}

	const FillStyle& GetFillStyle() const override
	{
		auto style = GetShapeAtIndex(0)->GetFillStyle();
		for (size_t i = 1; i < GetShapesCount(); ++i)
		{
			auto shape = GetShapeAtIndex(i);
			if (style.GetColor() != shape->GetFillStyle().GetColor())
			{
				LineStyle temp(0, std::nullopt);
				return temp;
			}
		}
		return GetShapeAtIndex(0)->GetFillStyle();
	}

	void Draw(gfx::ICanvas& canvas) const override
	{
		for (size_t i = 0; i < GetShapesCount(); ++i)
		{
			auto shape = GetShapeAtIndex(i);
			if (shape)
			{
				shape->Draw(canvas);
			}
		}
	}

	size_t GetShapesCount() const override
	{
		return m_shapes.size();
	}

	void InsertShape(const std::shared_ptr<IShape>& shape, size_t position) override
	{
		m_shapes.insert({ position, shape });
		m_fillStyle->InsertStyle(shape->GetFillStyle(), position);
		m_outlineStyle->InsertStyle(shape->GetOutlineStyle(), position);
	}

	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) const override
	{
		return m_shapes.at(index);
	}

	void RemoveShapeAtIndex(size_t index) override
	{
		auto it = m_shapes.find(index);
		if (it != m_shapes.end())
		{
			m_shapes.erase(it);
			m_fillStyle->RemoveStyleAtIndex(index);
			m_outlineStyle->RemoveStyleAtIndex(index);
		}
	}

private:
	std::unordered_map<size_t, std::shared_ptr<IShape>> m_shapes;
	std::unique_ptr<GroupStyle<LineStyle>> m_outlineStyle = std::make_unique<GroupStyle<LineStyle>>();
	std::unique_ptr<GroupStyle<FillStyle>> m_fillStyle = std::make_unique<GroupStyle<FillStyle>>();
};
