#pragma once

#include "Libs/graphics_lib.h"
#include "Libs/modern_graphics_lib.h"

namespace app
{
class ModernGraphicsClassAdapter
	: public graphics_lib::ICanvas
	, public modern_graphics_lib::ModernGraphicsRenderer
{
public:
	explicit ModernGraphicsClassAdapter(std::ostream& strm)
		: ModernGraphicsRenderer(strm)
		, m_start(0, 0)
		, m_color(0, 0, 0, 0)
	{
	}

	void SetColor(uint32_t rgbColor) override
	{
		// todo как задавать нулевую прозрачность
		// todo убрать значение a по умолчанию - done
		float r, g, b, a;
		if (rgbColor > 0xFFFFFF)
		{
			r = static_cast<float>((rgbColor >> 24) & 0xFF) / 255.0f;
			g = static_cast<float>((rgbColor >> 16) & 0xFF) / 255.0f;
			b = static_cast<float>((rgbColor >> 8) & 0xFF) / 255.0f;
			a = static_cast<float>(rgbColor & 0xFF) / 255.0f;
		}
		else
		{
			r = static_cast<float>((rgbColor >> 16) & 0xFF) / 255.0f;
			g = static_cast<float>((rgbColor >> 8) & 0xFF) / 255.0f;
			b = static_cast<float>(rgbColor & 0xFF) / 255.0f;
			a = 0xFF / 255.0f;
		}

		m_color = { r, g, b, a };
	}

	void MoveTo(int x, int y) override
	{
		m_start = { x, y };
	}

	void LineTo(int x, int y) override
	{
		modern_graphics_lib::Point end(x, y);

		DrawLine(m_start, end, m_color);

		m_start = end;
	}

private:
	modern_graphics_lib::RGBAColor m_color;
	modern_graphics_lib::Point m_start;
};
} // namespace app
