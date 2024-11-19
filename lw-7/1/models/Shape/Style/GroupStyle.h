#pragma once

#include "IStyle.h"
#include <memory>
#include <unordered_map>
#include <vector>

template <typename T>
class IGroupStyle : public IStyle
{
	virtual void InsertStyle(T& style, size_t position) = 0;
	virtual void RemoveStyleAtIndex(size_t index) = 0;
public:
	virtual ~IGroupStyle() = default;
};

template <typename T>
class GroupStyle : IGroupStyle<T>
{
public:
	void InsertStyle(T& style, size_t position) override
	{
		m_styles.insert({ position, style });
	}

	void RemoveStyleAtIndex(size_t index) override
	{
		auto it = m_styles.find(index);
		if (it != m_styles.end())
		{
			m_styles.erase(it);
		}
	}

	[[nodiscard]] std::optional<bool> IsEnabled() const override
	{
		if (m_styles.empty())
		{
			return std::nullopt;
		}

		std::optional<bool> enabled = std::nullopt;
		for (const auto& pair : m_styles)
		{
			if (enabled == std::nullopt)
			{
				enabled = pair.second.IsEnabled();
				continue;
			}

			if (enabled != pair.second.IsEnabled())
			{
				return std::nullopt;
			}
		}
		return enabled;
	}

	void Enable(bool enabled) override
	{
		m_enabled = enabled;
		for (const auto& pair : m_styles)
		{
			pair.second.Enable(enabled);
		}
	}

	[[nodiscard]] std::optional<RGBAColor> GetColor() const override
	{
		if (m_styles.empty())
		{
			return std::nullopt;
		}

		std::optional<RGBAColor> color = std::nullopt;
		for (const auto& pair : m_styles)
		{
			if (color == std::nullopt)
			{
				color = pair.second.GetColor();
				continue;
			}

			if (color != pair.second.GetColor())
			{
				return std::nullopt;
			}
		}
		return color;
	}

	void SetColor(RGBAColor color) override
	{
		m_color = color;
		for (const auto& pair : m_styles)
		{
			pair.second.SetColor(color);
		}
	}

	~GroupStyle() override = default;

private:
	std::optional<bool> m_enabled;
	std::optional<RGBAColor> m_color;
	std::unordered_map<size_t, T&> m_styles;
};