#pragma once

#include "ICanvas.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

namespace gfx
{
class CCanvasSVG : public ICanvas
{
public:
	explicit CCanvasSVG(unsigned int width = 900, unsigned int height = 900)
		: m_currentLineColor({ 255, 255, 255, 255 })
		, m_currentFillColor({ 255, 255, 255, 255 })
	{
		m_file << "<svg width=\"" << width << "\" height=\"" << height << "\" xmlns=\"http://www.w3.org/2000/svg\">\n";
	}

	void DrawEllipse(double cx, double cy, double rx, double ry) override
	{
		if (m_beginFill)
		{
			std::string ellipse = "<ellipse cx=\""
				+ std::to_string(cx) + "\" cy=\"" + std::to_string(cy)
				+ "\" rx=\"" + std::to_string(rx) + "\" ry=\""
				+ std::to_string(ry) + "\" ";
			m_buff.emplace_back(ellipse);
		}
		else
		{
			m_file << "<ellipse cx=\"" << cx << "\" cy=\"" << cy
				   << "\" rx=\"" << rx << "\" ry=\"" << ry
				   << "\" stroke=\"" << m_currentLineColor.ToString()
				   << "\" stroke-width=\"" << m_lineWidth
				   << "\" />\n";
		}
	}

	void SetLineColor(uint32_t color) override
	{
		m_currentLineColor = ToColor(color);
	};

	void SetFillColor(uint32_t color) override
	{
		m_currentFillColor = ToColor(color);
	};

	void SetLineWidth(double width) override
	{
		m_lineWidth = width;
	};

	void DrawLine(double x1, double y1, double x2, double y2) override
	{
		m_file << "<line x1=\"" << x1 << "\" y1=\"" << y1
			   << "\" x2=\"" << x2 << "\" y2=\"" << y2
			   << "\" stroke=\"" << m_currentLineColor.ToString()
			   << "\" stroke-width=\"" << m_lineWidth
			   << "\" />\n";
	};

	void BeginFill(uint32_t color) override
	{
		if (m_beginFill)
		{
			throw std::logic_error("You already start fill");
		}
		m_beginFill = true;
		m_currentFillColor = ToColor(color);
	};

	void EndFill() override
	{
		if (!m_beginFill)
		{
			throw std::logic_error("You can`t end fill without start");
		}
		m_beginFill = false;

		if (m_buff.empty())
		{
			return;
		}

		for (const auto& shape : m_buff)
		{
			m_file << shape
				   << "fill=\"" << m_currentFillColor.ToString()
				   << "\" stroke=\"" << m_currentLineColor.ToString()
				   << "\" stroke-width=\"" << m_lineWidth
				   << "\" />\n";
		}

		m_buff.clear();
	};

	void DrawPolygon(const std::vector<std::pair<double, double>>& vertices) override
	{
		if (vertices.empty())
		{
			return;
		}
		std::string polygon = "<polygon points=\"";

		for (const auto& line : vertices)
		{
			polygon += std::to_string(line.first) + "," + std::to_string(line.second) + " ";
		}
		polygon += "\" ";
		if (m_beginFill)
		{
			m_buff.emplace_back(polygon);
		}
		else
		{
			m_file << polygon
				   << "stroke=\"" << m_currentLineColor.ToString()
				   << "\" stroke-width=\"" << m_lineWidth
				   << "\" />\n";
		}
	};

	void SaveToFile(const std::string& filename)
	{
		if (m_beginFill)
		{
			EndFill();
		}
		m_file << "</svg>";
		std::string content = m_file.str();
		std::ofstream outFile(filename);
		std::cout << content;
		if (!outFile)
		{
			throw std::runtime_error("Failed to open output stream");
		}
		outFile << content;

		outFile.close();
	};

	~CCanvasSVG() override = default;

private:
	bool m_beginFill = false;
	Color m_currentLineColor{};
	Color m_currentFillColor{};
	std::vector<std::string> m_buff{};
	double m_lineWidth = 1;
	std::stringstream m_file{};
};
} // namespace gfx