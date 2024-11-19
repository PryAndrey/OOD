#pragma once

#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

namespace gfx
{

struct Color
{
	uint8_t r, g, b, a;

	[[nodiscard]] uint32_t ToNum() const
	{
		return (static_cast<uint32_t>(r) << 24) | (static_cast<uint32_t>(g) << 16) | (static_cast<uint32_t>(b) << 8) | (static_cast<uint32_t>(a));
	}

	[[nodiscard]] std::string ToString() const
	{
		std::stringstream ss;
		ss << std::hex << std::setfill('F') << std::setw(6) << ToNum();
		return "#" + ss.str();
	}
};

Color ToColor(uint32_t hexNum)
{
	Color result{};

	result.r = static_cast<uint8_t>((hexNum >> 24) & 0xFF);
	result.g = static_cast<uint8_t>((hexNum >> 16) & 0xFF);
	result.b = static_cast<uint8_t>((hexNum >> 8) & 0xFF);
	result.a = static_cast<uint8_t>(hexNum & 0xFF);
	return result;
}

Color ToColor(const std::string& color)
{
	Color result{};

	if (color.size() != 7 || color[0] != '#')
	{
		throw std::logic_error("Invalid color format");
	}
	std::string tempColor = color;
	tempColor.erase(tempColor.begin());
	uint32_t hexNum = std::stoul(tempColor, nullptr, 16);

	result.r = static_cast<uint8_t>((hexNum >> 24) & 0xFF);
	result.g = static_cast<uint8_t>((hexNum >> 16) & 0xFF);
	result.b = static_cast<uint8_t>((hexNum >> 8) & 0xFF);
	result.a = static_cast<uint8_t>(hexNum & 0xFF);

	return result;
}

class ICanvas
{
public:
	virtual void SetLineColor(uint32_t color) = 0;

	virtual void SetFillColor(uint32_t color) = 0;

	virtual void SetLineWidth(double width) = 0;

	virtual void DrawLine(double x1, double y1, double x2, double y2) = 0;

	virtual void BeginFill(uint32_t color) = 0;

	virtual void EndFill() = 0;

	virtual void DrawPolygon(const std::vector<std::pair<double, double>>& vertices) = 0;

	virtual void DrawEllipse(double cx, double cy, double rx, double ry) = 0;

	virtual ~ICanvas() = default;
};
} // namespace gfx