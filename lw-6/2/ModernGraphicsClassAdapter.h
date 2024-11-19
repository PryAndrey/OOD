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
	{
	}

	void MoveTo(int x, int y) override
	{
		if (!m_drawing)
		{
			BeginDraw();
		}
		m_start = { x, y };
	}

	void LineTo(int x, int y) override
	{
		if (!m_drawing)
		{
			BeginDraw();
		}
		const modern_graphics_lib::Point end(x, y);

		DrawLine(m_start, end);

		m_start = end;
	}

private:
	modern_graphics_lib::Point m_start;
};
} // namespace app
