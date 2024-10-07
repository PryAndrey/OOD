#include "../CColor.cpp"
#include "ICanvas.h"
// #include "../Shapes/CShape.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class CCanvasSVG : public gfx::ICanvas
{
public:
	explicit CCanvasSVG(unsigned int width = 900, unsigned int height = 900)
		: m_width(width), m_height(height), m_currentColor(0xffffff), m_currentX(0), m_currentY(0)
	{
		m_file.open("../../4/canvas.svg", std::ios::out);
		m_file << "<svg width=\"" << width << "\" height=\"" << height << "\" xmlns=\"http://www.w3.org/2000/svg\">\n";
	}

	~CCanvasSVG() override
	{
		m_file << "</svg>";
		m_file.close();
	}

	void DrawText(double left, double top, double fontSize, const std::string& textValue) override
	{
		m_file << "<text x=\"" << left << "\" y=\"" << top << "\" font-size=\"" << fontSize
			   << "\" fill=\"" << m_currentColor.ToString()
			   << R"(" style="font-weight:bold;">)" << textValue << "</text>\n";
	}

	void DrawEllipse(double cx, double cy, double rx, double ry) override
	{
		m_file << "<ellipse cx=\"" << cx << "\" cy=\"" << cy
			   << "\" rx=\"" << rx << "\" ry=\"" << ry
			   << "\" fill=\"" << m_currentColor.ToString()
			   << "\" />\n";
	}

	void LineTo(double x, double y) override
	{
		m_lines.push_back({m_currentX, m_currentY, x, y});
		MoveTo(x, y);
	}

	void MoveTo(double x, double y) override
	{
		m_currentX = x;
		m_currentY = y;
	}

	void SetColor(const std::string& color) override
	{
		m_currentColor = Colors::ColorFabric(color);
	}

	void Fill() override
	{
		if (m_lines.empty()) {
			return;
		}

		m_file << "<polygon points=\"";

		for (const auto& line : m_lines) {
			m_file << line.x1 << "," << line.y1 << " ";
		}
		m_file << m_currentX << "," << m_currentY << " ";

		m_file << "\" fill=\"" << m_currentColor.ToString()
			   << "\" stroke=\"" << m_currentColor.ToString()
								 << "\" />\n";

		m_lines.clear();
	}

private:
	struct Line
	{
		double x1, y1, x2, y2;
	};

	unsigned int m_width, m_height;
	double m_currentX, m_currentY;
	Colors::CColor m_currentColor;
	std::fstream m_file;
	std::vector<Line> m_lines{};

};