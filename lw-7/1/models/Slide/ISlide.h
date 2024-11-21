#pragma once
#include "../IDrawable.h"
#include "../Shape/IGroupShape.h"

class ISlide : public IDrawable
{
public:
	[[nodiscard]] virtual double GetWidth() const = 0;
	[[nodiscard]] virtual double GetHeight() const = 0;

	virtual std::shared_ptr<IShape> GetShapeAtIndex(size_t index) = 0;
	virtual void InsertShape(const std::shared_ptr<IShape>& shape, size_t index) = 0;
	virtual void RemoveShapeAtIndex(size_t index) = 0;

	~ISlide() override = default;
};
