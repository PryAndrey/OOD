#pragma once

#include "Libs/graphics_lib.h"
#include "Libs/modern_graphics_lib.h"

namespace app
{
class ModernGraphicsAdapter : public graphics_lib::ICanvas
{
public:
	explicit ModernGraphicsAdapter(modern_graphics_lib::ModernGraphicsRenderer& modernRenderer)
		: m_renderer(modernRenderer)
		, m_start(0, 0)
		, m_color(0, 0, 0, 0)
	{
	}

	void SetColor(uint32_t rgbColor) override
	{
		float r, g, b, a = 0xFF;
		if (rgbColor > 0xFFFFFF)
		{//static_cast to float
			r = ((rgbColor >> 24) & 0xFF) / 255.0f;
			g = ((rgbColor >> 16) & 0xFF) / 255.0f;
			b = ((rgbColor >> 8) & 0xFF) / 255.0f;
			a = (rgbColor & 0xFF) / 255.0f;
		}
		else
		{
			r = ((rgbColor >> 16) & 0xFF) / 255.0f;
			g = ((rgbColor >> 8) & 0xFF) / 255.0f;
			b = (rgbColor & 0xFF) / 255.0f;
		}
		m_color = { r, g, b, a };
	}

	void MoveTo(int x, int y) override
	{
		m_start = { x, y };
	}

	void LineTo(int x, int y) override
	{
		const modern_graphics_lib::Point end(x, y);

		m_renderer.DrawLine(m_start, end, m_color);

		m_start = end;
	}

private:
	modern_graphics_lib::RGBAColor m_color;
	modern_graphics_lib::Point m_start;
	modern_graphics_lib::ModernGraphicsRenderer& m_renderer;
};
} // namespace app
