#pragma once

#include "../StyleEnumerator.h"
#include "IFillStyle.h"
#include <memory>
#include <unordered_map>
#include <vector>

class GroupFillStyle : public IFillStyle
{
public:
	explicit GroupFillStyle(std::unique_ptr<IStyleEnumerator<IFillStyle>> enumerator, bool isEnabled = true)
		: m_enumerator(std::move(enumerator))
	{
		Enable(isEnabled);
	};

	[[nodiscard]] std::optional<RGBAColor> GetColor() const override
	{
		std::optional<RGBAColor> prevColor = std::nullopt;
		std::optional<RGBAColor> currColor = std::nullopt;
		std::optional<RGBAColor> resultColor = std::nullopt;

		m_enumerator->EnumerateAll([&](const std::shared_ptr<IFillStyle>& stylePtr) {
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
		m_enumerator->EnumerateAll([color](const std::shared_ptr<IFillStyle>& stylePtr) {
			stylePtr->SetColor(color);
		});

		m_color = color;
	}

	[[nodiscard]] std::optional<bool> IsEnabled() const override
	{
		std::optional<double> prevIsEnabled = std::nullopt;
		std::optional<double> currIsEnabled = std::nullopt;
		std::optional<double> resultIsEnabled = std::nullopt;

		m_enumerator->EnumerateAll([&](const std::shared_ptr<IFillStyle>& stylePtr) {
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
		m_enumerator->EnumerateAll([enable](const std::shared_ptr<IFillStyle>& stylePtr) {
			stylePtr->Enable(enable);
		});

		m_enabled = enable;
	}

	~GroupFillStyle() override = default;

private:
	std::unique_ptr<IStyleEnumerator<IFillStyle>> m_enumerator;
	std::optional<RGBAColor> m_color = std::nullopt;
	double m_width = 0;
};
