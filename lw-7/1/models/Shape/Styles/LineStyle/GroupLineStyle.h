#pragma once

#include "../StyleEnumerator.h"
#include "ILineStyle.h"
#include <memory>
#include <unordered_map>
#include <vector>

class GroupLineStyle : public ILineStyle
{
public:
	explicit GroupLineStyle(std::unique_ptr<IStyleEnumerator<ILineStyle>> enumerator, bool isEnabled = true)
		: m_enumerator(std::move(enumerator))
	{
		Enable(isEnabled);
	};

	[[nodiscard]] std::optional<RGBAColor> GetColor() const override
	{
		std::optional<RGBAColor> prevColor = std::nullopt;
		std::optional<RGBAColor> currColor = std::nullopt;
		std::optional<RGBAColor> resultColor = std::nullopt;

		m_enumerator->EnumerateAll([&](const std::shared_ptr<ILineStyle>& stylePtr) {
			currColor = stylePtr->GetColor();
			if (prevColor == std::nullopt)
			{
				prevColor = currColor;
				resultColor = currColor;
			}

			if (resultColor != std::nullopt && prevColor != currColor)
			{
				resultColor = std::nullopt;
			}
		});

		return resultColor;
	}

	void SetColor(RGBAColor color) override
	{
		m_enumerator->EnumerateAll([color](const std::shared_ptr<ILineStyle>& stylePtr) {
			stylePtr->SetColor(color);
		});

		m_color = color;
	}

	[[nodiscard]] double GetWidth() const override
	{
		if (IsEnabled())
		{
			return m_width;
		}
		std::optional<double> prevWidth = std::nullopt;
		std::optional<double> currWidth = std::nullopt;
		std::optional<double> resultWidth = std::nullopt;

		m_enumerator->EnumerateAll([&](const std::shared_ptr<ILineStyle>& stylePtr) {
			currWidth = stylePtr->GetWidth();
			if (prevWidth == std::nullopt)
			{
				prevWidth = currWidth;
				resultWidth = currWidth;
			}

			if (resultWidth != std::nullopt && prevWidth != currWidth)
			{
				resultWidth = std::nullopt;
			}
		});

		return resultWidth.value();
	}

	void SetWidth(double width) override
	{
		m_enumerator->EnumerateAll([width](const std::shared_ptr<ILineStyle>& stylePtr) {
			stylePtr->SetWidth(width);
		});

		m_width = width;
	}

	[[nodiscard]] std::optional<bool> IsEnabled() const override
	{
		std::optional<double> prevIsEnabled = std::nullopt;
		std::optional<double> currIsEnabled = std::nullopt;
		std::optional<double> resultIsEnabled = std::nullopt;

		m_enumerator->EnumerateAll([&](const std::shared_ptr<ILineStyle>& stylePtr) {
			currIsEnabled = stylePtr->IsEnabled();
			if (prevIsEnabled == std::nullopt)
			{
				prevIsEnabled = currIsEnabled;
				resultIsEnabled = currIsEnabled;
			}

			if (resultIsEnabled != std::nullopt && prevIsEnabled != currIsEnabled)
			{
				resultIsEnabled = std::nullopt;
			}
		});

		return resultIsEnabled.value();
	}

	void Enable(bool enable) override
	{
		m_enumerator->EnumerateAll([enable](const std::shared_ptr<ILineStyle>& stylePtr) {
			stylePtr->Enable(enable);
		});

		m_enabled = enable;
	}

	~GroupLineStyle() override = default;

private:
	std::unique_ptr<IStyleEnumerator<ILineStyle>> m_enumerator;
	std::optional<RGBAColor> m_color = std::nullopt;
	double m_width = 0;
};
