#pragma once

#include "CShapeService.h"
using namespace std;
const string SPACE = R"(\s+)";
const string DIGIT = R"((\d+(?:\.\d+)?))";
const string MAYBE_NEG_DIGIT = R"((-?\d+(?:\.\d+)?))";
const string POINT = MAYBE_NEG_DIGIT + SPACE + MAYBE_NEG_DIGIT;
const string COLOR = R"(([0-9abcdef]{8}))";

string OPTIONAL(const string& PARAM)
{
	return R"((:?)" + PARAM + R"()?)";
}

std::vector<RegexPair> CShapeService::GetRegexPairs()
{
	return {
		{ regex(R"(rectangle\s+)" + POINT + SPACE + DIGIT + SPACE + DIGIT + OPTIONAL(SPACE + COLOR) + OPTIONAL(SPACE + COLOR)),
			[this](const smatch& match) { RectangleFabric(match); } },
		{ regex(R"(triangle\s+)" + POINT + SPACE + POINT + SPACE + POINT + OPTIONAL(SPACE + COLOR) + OPTIONAL(SPACE + COLOR)),
			[this](const smatch& match) { TriangleFabric(match); } },
		{ regex(R"(circle\s+)" + POINT + SPACE + DIGIT + OPTIONAL(SPACE + COLOR) + OPTIONAL(SPACE + COLOR)),
			[this](const smatch& match) { CircleFabric(match); } },
		{ regex(R"(line\s+)" + POINT + SPACE + POINT + OPTIONAL(SPACE + COLOR)),
			[this](const smatch& match) { LineFabric(match); } },
		{ regex(R"(\/\/.*|)"),
			[](const smatch& match) {} }
	};
}

CColor CShapeService::ColorFabric(const string& strColor, uint32_t templateColor)
{
	if (strColor.empty())
	{
		return CColor(templateColor);
	}
	std::stringstream ss;
	ss << "0x" << strColor;
	uint32_t color;
	ss >> hex >> color;
	return CColor(color);
}

void CShapeService::ReadShapes(istream& inputStream)
{
	vector<RegexPair> regexPairs = GetRegexPairs();
	string line;
	while (getline(inputStream, line))
	{
		if (line == "!")
			break;
		bool noRegex = true;
		transform(line.begin(), line.end(), line.begin(), ::tolower);
		for (auto& regexPair : regexPairs)
		{
			smatch match;
			if (regex_match(line, match, regexPair.first))
			{
				regexPair.second(match);
				noRegex = false;
				break;
			}
		}
		if (noRegex)
			cout << "Unknown command" << endl;
	}
}

ISolidShape* CShapeService::GetMaxAreaShape() const
{
	if (m_shapes.empty())
		return nullptr;
	auto maxAreaShape = max_element(m_shapes.begin(), m_shapes.end(),
		[](const auto& a, const auto& b) { return a->GetArea() < b->GetArea(); });
	return maxAreaShape->get();
}
ISolidShape* CShapeService::GetMinPerimeterShape() const
{
	if (m_shapes.empty())
		return nullptr;
	auto minPerimeterShape = min_element(m_shapes.begin(), m_shapes.end(),
		[](const auto& a, const auto& b) { return a->GetPerimeter() < b->GetPerimeter(); });
	return minPerimeterShape->get();
}

void CShapeService::RectangleFabric(const std::smatch& match)
{
	double x = stod(match[1]);
	double y = stod(match[2]);
	double width = stod(match[3]);
	double height = stod(match[4]);
	string outlineColorStr = match[6];
	string fillColorStr = match[8];

	CColor outlineColor = ColorFabric(outlineColorStr, Colors::BLACK);
	CColor fillColor = ColorFabric(fillColorStr, Colors::TRANSPARENT);

	m_shapes.emplace_back(
		make_unique<CRectangle>(CPoint(x, y), width, height, outlineColor, fillColor));
	m_drawableShapes.emplace_back(
		make_unique<CRectangle>(CPoint(x, y), width, height, outlineColor, fillColor));
}
void CShapeService::TriangleFabric(const std::smatch& match)
{
	double x1 = stod(match[1]), y1 = stod(match[2]);
	double x2 = stod(match[3]), y2 = stod(match[4]);
	double x3 = stod(match[5]), y3 = stod(match[6]);
	string outlineColorStr = match[8];
	string fillColorStr = match[10];

	CColor outlineColor = ColorFabric(outlineColorStr, Colors::BLACK);
	CColor fillColor = ColorFabric(fillColorStr, Colors::TRANSPARENT);

	m_shapes.emplace_back(
		make_unique<CTriangle>(
			CPoint(x1, y1),
			CPoint(x2, y2),
			CPoint(x3, y3),
			outlineColor, fillColor));
	m_drawableShapes.emplace_back(
		make_unique<CTriangle>(
			CPoint(x1, y1),
			CPoint(x2, y2),
			CPoint(x3, y3),
			outlineColor, fillColor));
}
void CShapeService::CircleFabric(const std::smatch& match)
{
	double x = stod(match[1]);
	double y = stod(match[2]);
	double radius = stod(match[3]);
	string outlineColorStr = match[5];
	string fillColorStr = match[7];

	CColor outlineColor = ColorFabric(outlineColorStr, Colors::BLACK);
	CColor fillColor = ColorFabric(fillColorStr, Colors::TRANSPARENT);

	m_shapes.emplace_back(
		make_unique<CCircle>(CPoint(x, y), radius, outlineColor, fillColor));
	m_drawableShapes.emplace_back(
		make_unique<CCircle>(CPoint(x, y), radius, outlineColor, fillColor));
}
void CShapeService::LineFabric(const std::smatch& match)
{
	double x1 = stod(match[1]);
	double y1 = stod(match[2]);
	double x2 = stod(match[3]);
	double y2 = stod(match[4]);
	string outlineColorStr = match[6];

	CColor outlineColor = ColorFabric(outlineColorStr, Colors::BLACK);

	m_drawableShapes.emplace_back(
		make_unique<CLineSegment>(CPoint(x1, y1), CPoint(x2, y2), outlineColor));
}

void CShapeService::RenderShapes()
{
	ICanvas* m_canvas = new CCanvasSFML(900, 900);
	for (auto& shape : m_drawableShapes)
	{
		shape->Draw(m_canvas);
	}
	m_canvas->Display();
}
