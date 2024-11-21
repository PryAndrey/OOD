#pragma once
#include "IShape.h"
#include <cstdint>
#include <limits>
#include <memory>

class IGroupShape : public IShape
{
public:
	[[nodiscard]] virtual size_t GetShapesCount() const = 0;
	virtual void InsertShape(const std::shared_ptr<IShape>& shape, size_t position) = 0;
	[[nodiscard]] virtual std::shared_ptr<IShape> GetShapeAtIndex(size_t index) const = 0;
	virtual void RemoveShapeAtIndex(size_t index) = 0;
	[[nodiscard]] virtual std::shared_ptr<const IShape> GetGroupShape() const = 0;

	virtual ~IGroupShape() = default;
};