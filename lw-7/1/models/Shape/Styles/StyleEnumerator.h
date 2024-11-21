#pragma once

#include "FillStyle/IFillStyle.h"
#include <functional>
#include <memory>

template <typename T>
class IStyleEnumerator
{
public:
	virtual ~IStyleEnumerator() = default;
	virtual void EnumerateAll(std::function<void(std::shared_ptr<T>)>) = 0;
};

template <typename T>
class LineStyleEnumerator : public IStyleEnumerator<ILineStyle>
{
public:
	explicit LineStyleEnumerator(T& items)
		: m_items(items)
	{
	}

	void EnumerateAll(std::function<void(std::shared_ptr<ILineStyle>)> callback) override
	{
		for (auto& item : m_items)
		{
			callback(item->GetOutlineStyle());
		}
	}

private:
	T& m_items;
};

template <typename T>
class FillStyleEnumerator : public IStyleEnumerator<IFillStyle>
{
public:
	explicit FillStyleEnumerator(T& items)
		: m_items(items)
	{
	}

	void EnumerateAll(std::function<void(std::shared_ptr<IFillStyle>)> callback) override
	{
		for (auto& item : m_items)
		{
			callback(item->GetFillStyle());
		}
	}

private:
	T& m_items;
};