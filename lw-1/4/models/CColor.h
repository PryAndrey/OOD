#pragma once

#include <iomanip>
namespace Colors
{
constexpr uint32_t RED = 0xff0000ff;
constexpr uint32_t GREEN = 0x00ff00ff;
constexpr uint32_t BLUE = 0x0000ffff;
constexpr uint32_t WHITE = 0xffffffff;
constexpr uint32_t BLACK = 0x000000ff;
constexpr uint32_t TRANSPARENT = 0x00000000;
}

class CColor
{
public:
	explicit CColor(uint32_t color)
		: m_color(color)
	{
	}

	[[nodiscard]] uint32_t GetColor() const
	{
		return m_color;
	}

	[[nodiscard]] unsigned char GetRed() const
	{
		return (m_color >> 24) & 0xFF;
	}
	[[nodiscard]] unsigned char GetGreen() const
	{
		return (m_color >> 16) & 0xFF;
	}
	[[nodiscard]] unsigned char GetBlue() const
	{
		return (m_color >> 8) & 0xFF;
	}
	[[nodiscard]] unsigned char GetAlpha() const
	{
		return m_color & 0xFF;
	}

	[[nodiscard]] std::string ToString() const
	{
		std::stringstream ss;
		ss << std::hex << std::setfill('0') << std::setw(8) << m_color;
		return ss.str();
	}

private:
	uint32_t m_color;
};