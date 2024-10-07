#pragma once

#include "CCanvas.h"
#include "models/CColor.cpp"
#include "models/Picture/CPicture.cpp"
#include "models/Shapes/ShapesStrategy/Circle/CCircleShapeType.cpp"
#include "models/Shapes/ShapesStrategy/Line/CLineShapeType.cpp"
#include "models/Shapes/ShapesStrategy/Rectangle/CRectangleShapeType.cpp"
#include "models/Shapes/ShapesStrategy/Text/CTextShapeType.cpp"
#include "models/Shapes/ShapesStrategy/Triangle/CTriangleShapeType.cpp"
#include <iostream>
#include <regex>
#include <string>

namespace reg
{
const std::string ID = R"(([\w\d]+))";
const std::string SPACE = R"(\s+)";
const std::string DIGIT = R"((-?\d+(?:\.\d+)?))";
const std::string COORD = DIGIT + SPACE + DIGIT;
const std::string COLOR = R"(#([0-9A-Fa-f]{6}))";
}; // namespace reg
/*
AddShape sh1 #F010F0 rectangle 400 400 100 100
AddShape sh2 #F010F0 triangle 400 400 500 400 450 300
AddShape sh3 #F010F0 line 200 400 200 600
AddShape sh4 #F010F0 circle 200 350 100
AddShape sh5 #F010F0 text 200 350 50 hello world
DrawPicture
 */

/// Вынести из namespace Ccanvas - done
/// Разбить на функции - done
/// Актуализировать диаграмму - done
/// Убрать функции из picture над 1 фигурой(сделать через id)
using namespace std;

using RegexCommandPair = std::pair<std::regex, std::function<void(std::smatch match, shapes::CPicture& picture)>>;
using RegexShapePair = std::pair<std::regex, std::function<shapes::IShapeType*(std::smatch match)>>;

//unique_ptr
shapes::IShapeType* Rectangle(const smatch& match)
{
	double x = stod(match[1].str());
	double y = stod(match[2].str());
	double width = stod(match[3].str());
	double height = stod(match[4].str());

	return new shapes::CRectangleShapeType(x, y, width, height);
}
shapes::IShapeType* Circle(const smatch& match)
{
	double x = stod(match[1].str());
	double y = stod(match[2].str());
	double r = stod(match[3].str());

	return new shapes::CCircleShapeType(x, y, r);
}
shapes::IShapeType* Line(const smatch& match)
{
	double x1 = stod(match[1].str());
	double y1 = stod(match[2].str());
	double x2 = stod(match[3].str());
	double y2 = stod(match[4].str());

	return new shapes::CLineShapeType(x1, y1, x2, y2);
}
shapes::IShapeType* Triangle(const smatch& match)
{
	double x1 = stod(match[1].str());
	double y1 = stod(match[2].str());
	double x2 = stod(match[3].str());
	double y2 = stod(match[4].str());
	double x3 = stod(match[5].str());
	double y3 = stod(match[6].str());

	return new shapes::CTriangleShapeType(x1, y1, x2, y2, x3, y3);
}
shapes::IShapeType* Text(const smatch& match)
{
	double x = stod(match[1].str());
	double y = stod(match[2].str());
	double size = stod(match[3].str());
	string text = match[4].str();

	return new shapes::CTextShapeType(x, y, size, text);
}

vector<RegexShapePair> GetRegexShapePairs()
{
	vector<RegexShapePair> regexShapePairs{
		{
			{ regex(R"(^rectangle)" + reg::SPACE + reg::COORD + reg::SPACE + reg::DIGIT + reg::SPACE + reg::DIGIT + R"($)"),
				Rectangle },
			{ regex(R"(^circle)" + reg::SPACE + reg::COORD + reg::SPACE + reg::DIGIT + R"($)"),
				Circle },
			{ regex(R"(^line)" + reg::SPACE + reg::COORD + reg::SPACE + reg::COORD + R"($)"),
				Line },
			{ regex(R"(^text)" + reg::SPACE + reg::COORD + reg::SPACE + reg::DIGIT + reg::SPACE + R"((.+))"),
				Text },
			{ regex(R"(^triangle)" + reg::SPACE + reg::COORD + reg::SPACE + reg::COORD + reg::SPACE + reg::COORD + R"($)"),
				Triangle },
		}
	};
	return regexShapePairs;
}

void AddShape(const smatch& match, shapes::CPicture& picture)
{
	string id = match[2].str();
	string color = match[3].str();
	string shapeInfo = match[4].str();

	vector<RegexShapePair> regexShapePairs = GetRegexShapePairs();
	for (const auto& regexShapePair : regexShapePairs)
	{
		smatch shapeMatch;
		if (regex_match(shapeInfo, shapeMatch, regexShapePair.first))
		{
			std::unique_ptr<shapes::IShapeType> newShapeType(regexShapePair.second(shapeMatch));
			std::unique_ptr<shapes::CShape> newShape = std::make_unique<shapes::CShape>(id, color, std::move(newShapeType));
			picture.AddShape(id, std::move(newShape));
			return;
		}
	}
}
void ChangeShape(const smatch& match, shapes::CPicture& picture)
{
	string id = match[2].str();
	string shapeInfo = match[3].str();

	vector<RegexShapePair> regexShapePairs = GetRegexShapePairs();
	for (const auto& regexShapePair : regexShapePairs)
	{
		smatch shapeMatch;
		if (regex_match(shapeInfo, shapeMatch, regexShapePair.first))
		{
			std::unique_ptr<shapes::IShapeType> newShapeType(regexShapePair.second(shapeMatch));
			picture.ChangeShape(id, std::move(newShapeType));
			return;
		}
	}
}
void ChangeColor(const smatch& match, shapes::CPicture& picture)
{
	string id = match[2].str();
	string color = match[3].str();
	picture.ChangeColor(id, color);
}
void DeleteShape(const smatch& match, shapes::CPicture& picture)
{
	string id = match[2].str();
	picture.DeleteShape(id);
}
void MoveShape(const smatch& match, shapes::CPicture& picture)
{
	string id = match[2].str();
	double dx = stod(match[3].str());
	double dy = stod(match[4].str());
	picture.MoveShape(id, dx, dy);
}
void DrawShape(const smatch& match, shapes::CPicture& picture)
{
	string id = match[2].str();
	CCanvasSVG canvas(900, 900);
	picture.DrawShape(id, canvas);
}
void MovePicture(const smatch& match, shapes::CPicture& picture)
{
	double dx = stod(match[2].str());
	double dy = stod(match[3].str());
	picture.MovePicture(dx, dy);
}
void List(const smatch& match, shapes::CPicture& picture)
{
	picture.List();
}
void DrawPicture(const smatch& match, shapes::CPicture& picture)
{
	CCanvasSVG canvas(900, 900);
	picture.DrawPicture(canvas);
}

vector<RegexCommandPair> GetRegexCommandPairs()
{
	vector<RegexCommandPair> regexCommandPairs{
		{ regex(R"((AddShape))" + reg::SPACE + reg::ID + reg::SPACE + reg::COLOR + reg::SPACE + R"((.+))"),
			AddShape },
		{ regex(R"((ChangeShape))" + reg::SPACE + reg::ID + reg::SPACE + R"((.+))"),
			ChangeShape },
		{ regex(R"((ChangeColor))" + reg::SPACE + reg::ID + reg::SPACE + reg::COLOR),
			ChangeColor },
		{ regex(R"((DeleteShape))" + reg::SPACE + reg::ID),
			DeleteShape },
		{ regex(R"((MoveShape))" + reg::SPACE + reg::ID + reg::SPACE + reg::COORD),
			MoveShape },
		{ regex(R"((DrawShape))" + reg::SPACE + reg::ID),
			DrawShape },
		{ regex(R"((MovePicture))" + reg::SPACE + reg::COORD),
			MovePicture },
		{ regex(R"((List))"),
			List },
		{ regex(R"((DrawPicture))"),
			DrawPicture }
	};
	return regexCommandPairs;
}

void LineProcessor(const std::string& line, shapes::CPicture& picture)
{
	vector<RegexCommandPair> regexPairs = GetRegexCommandPairs();
	for (const auto& regexPair : regexPairs)
	{
		smatch match;
		if (regex_match(line, match, regexPair.first))
		{
			try
			{
				regexPair.second(match, picture);
				return;
			}
			catch (std::invalid_argument& err)
			{
				cout << err.what() << endl;
				return;
			}
		}
	}
	cout << "Error: unknown command" << endl;
}

void ShapeCommandProcessor(istream& myCin)
{
	shapes::CPicture picture;
	string line;
	while (getline(myCin, line))
	{
		if (line == "!")
		{
			break;
		}
		LineProcessor(line, picture);
	}
}
