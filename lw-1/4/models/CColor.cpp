#ifndef CCOLOR_H
#define CCOLOR_H

#include <iomanip>
namespace Colors
{
constexpr uint32_t RED = 0xff0000;
constexpr uint32_t GREEN = 0x00ff00;
constexpr uint32_t BLUE = 0x0000ff;
constexpr uint32_t WHITE = 0xffffff;
constexpr uint32_t BLACK = 0x000000;

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
		return (m_color >> 16) & 0xFF;
	}
	[[nodiscard]] unsigned char GetGreen() const
	{
		return (m_color >> 8) & 0xFF;
	}
	[[nodiscard]] unsigned char GetBlue() const
	{
		return m_color & 0xFF;
	}

	[[nodiscard]] std::string ToString() const
	{
		std::stringstream ss;
		ss << std::hex << std::setfill('0') << std::setw(6) << m_color;
		return "#" + ss.str();
	}

private:
	uint32_t m_color;
};

CColor ColorFabric(const std::string& strColor)
{
	if (strColor.empty())
	{
		return CColor(BLACK);
	}
	std::stringstream ss;
	ss << "0x" << strColor;
	uint32_t color;
	ss >> std::hex >> color;
	return CColor(color);
}

} // namespace Colors

#endif // CCOLOR_H