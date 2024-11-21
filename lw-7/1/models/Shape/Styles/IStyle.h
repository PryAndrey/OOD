#pragma once

#include "../../CoreTypes.h"
#include <optional>

class IStyle
{
public:
	[[nodiscard]] virtual std::optional<bool> IsEnabled() const = 0;
	virtual void Enable(bool enable) = 0;

	[[nodiscard]] virtual std::optional<RGBAColor> GetColor() const = 0;
	virtual void SetColor(RGBAColor color) = 0;

	virtual ~IStyle() = default;
};

class Style : public IStyle
{
public:
	[[nodiscard]] std::optional<bool> IsEnabled() const override
	{
		return m_enabled;
	}

	void Enable(bool enable) override
	{
		m_enabled = enable;
	}

	~Style() override = default;

protected:
	std::optional<bool> m_enabled = std::nullopt;
};
