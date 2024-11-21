#pragma once

#include "IGroupShape.h"
#include "IShape.h"
#include "Styles/FillStyle/GroupFillStyle.h"
#include "Styles/LineStyle/GroupLineStyle.h"
#include <unordered_map>

using ShapesVec = std::vector<std::shared_ptr<IShape>>;

class GroupShape : public IGroupShape
	, std::enable_shared_from_this<GroupShape>
{
public:
	constexpr static const char* typeStart = "group_start";
	constexpr static const char* typeEnd = "group_end";

	GroupShape()
		: m_outlineStyle(std::make_shared<GroupLineStyle>(std::make_unique<LineStyleEnumerator<ShapesVec>>(m_shapes)))
		, m_fillStyle(std::make_shared<GroupFillStyle>(std::make_unique<FillStyleEnumerator<ShapesVec>>(m_shapes))) {};

	explicit GroupShape(std::vector<std::shared_ptr<IShape>>& shapes)
		: m_shapes(shapes)
		, m_outlineStyle(std::make_shared<GroupLineStyle>(std::make_unique<LineStyleEnumerator<ShapesVec>>(m_shapes)))
		, m_fillStyle(std::make_shared<GroupFillStyle>(std::make_unique<FillStyleEnumerator<ShapesVec>>(m_shapes))) {};

	RectD GetFrame() const override
	{
		double left = std::numeric_limits<double>::max();
		double top = std::numeric_limits<double>::max();
		double right = std::numeric_limits<double>::lowest();
		double bottom = std::numeric_limits<double>::lowest();

		for (const auto& shape : m_shapes)
		{
			RectD frame = shape->GetFrame();
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

		for (const auto& shape : m_shapes)
		{
			const RectD shapeFrame = shape->GetFrame();
			const double newLeft = rect.left + (shapeFrame.left - left) * scaleX;
			const double newTop = rect.top + (shapeFrame.top - top) * scaleY;
			const double newWidth = shapeFrame.width * scaleX;
			const double newHeight = shapeFrame.height * scaleY;
			shape->SetFrame({ newLeft, newTop, newWidth, newHeight });
		}
	}

	std::shared_ptr<ILineStyle> GetOutlineStyle() override
	{
		return m_outlineStyle;
	}

	std::shared_ptr<const ILineStyle> GetOutlineStyle() const override
	{
		return m_outlineStyle;
	}

	std::shared_ptr<IFillStyle> GetFillStyle() override
	{
		return m_fillStyle;
	}

	std::shared_ptr<const IFillStyle> GetFillStyle() const override
	{
		return m_fillStyle;
	}

	void Draw(gfx::ICanvas& canvas) const override
	{
		for (auto& shape : m_shapes)
		{
			shape->Draw(canvas);
		}
	}

	size_t GetShapesCount() const override
	{
		return m_shapes.size();
	}

	void InsertShape(const std::shared_ptr<IShape>& shape, size_t position) override
	{
		if (m_shapes.size() < position)
		{
			throw std::out_of_range("Out of range position");
		}

		m_shapes.insert(m_shapes.begin() + position, shape);
	}

	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) const override
	{
		return m_shapes.at(index);
	}

	void RemoveShapeAtIndex(size_t index) override
	{
		if (m_shapes.size() <= index)
		{
			throw std::out_of_range("Out of range index");
		}

		m_shapes.erase(m_shapes.begin() + index);
	}

	std::shared_ptr<const IShape> GetGroupShape() const override
	{
		return shared_from_this();
	}

	~GroupShape() override = default;

private:
	std::shared_ptr<const GroupShape> GetPtr() const
	{
		return shared_from_this();
	};

	std::vector<std::shared_ptr<IShape>> m_shapes;
	std::shared_ptr<GroupLineStyle> m_outlineStyle;
	std::shared_ptr<GroupFillStyle> m_fillStyle;
};
