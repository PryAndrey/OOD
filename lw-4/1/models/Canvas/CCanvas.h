#include "../CPoint.h"
#include "ICanvas.h"
#include "../CColor.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class CCanvasSVG : public gfx::ICanvas {
public:
    explicit CCanvasSVG(unsigned int width = 900, unsigned int height = 900)
            : m_width(width), m_height(height), m_currentColor(0xffffff) {
        m_file.open("../../1/canvas.svg", std::ios::out);
        m_file << "<svg width=\"" << width << "\" height=\"" << height << "\" xmlns=\"http://www.w3.org/2000/svg\">\n";
    }

    ~CCanvasSVG() override {
        m_file << "</svg>";
        m_file.close();
    }

    void DrawEllipse(double cx, double cy, double rx, double ry) override {
        m_file << "<ellipse cx=\"" << cx << "\" cy=\"" << cy
               << "\" rx=\"" << rx << "\" ry=\"" << ry
               << "\" fill=\"" << m_currentColor.ToString()
               << "\" />\n";
    }

    void DrawLine(CPoint from, CPoint to) override {
        m_lines.push_back({from.x, from.y, to.x, to.y});
    }

    void SetColor(const std::string &color) override {
        m_currentColor = Colors::CColor(color);
    }

    void Fill() override {
        if (m_lines.empty()) {
            return;
        }

        m_file << "<polygon points=\"";

        for (const auto &line: m_lines) {
            m_file << line.x1 << "," << line.y1 << " " << line.x2 << "," << line.y2 << " ";
        }

        m_file << "\" fill=\"" << m_currentColor.ToString()
               << "\" stroke=\"" << m_currentColor.ToString()
               << "\" />\n";

        m_lines.clear();
    }

private:
    struct Line {
        double x1, y1, x2, y2;
    };

    unsigned int m_width, m_height;
    Colors::CColor m_currentColor;
    std::fstream m_file;
    std::vector<Line> m_lines{};

};