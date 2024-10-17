#pragma once

#include "CShapeFactory.h"
#include "Shapes/Rectangle/CRectangle.h"
#include "Shapes/Triangle/CTriangle.h"
#include "Shapes/Ellipse/CEllipse.h"
#include "Shapes/Polygon/CPolygon.h"

using namespace std;

std::shared_ptr<shapes::CShape> MakeRectangle(const smatch &match) {
    string color = match[1].str();
    double x = stod(match[2].str());
    double y = stod(match[3].str());
    double width = stod(match[4].str());
    double height = stod(match[5].str());

    return std::make_shared<shapes::CRectangle>(color, x, y, width, height);
}

std::shared_ptr<shapes::CShape> MakeEllipse(const smatch &match) {
    string color = match[1].str();
    double x = stod(match[2].str());
    double y = stod(match[3].str());
    double rH = stod(match[4].str());
    double rV = stod(match[5].str());

    return std::make_shared<shapes::CEllipse>(color, x, y, rH, rV);
}

std::shared_ptr<shapes::CShape> MakePolygon(const smatch &match) {
    string color = match[1].str();
    double x = stod(match[2].str());
    double y = stod(match[3].str());
    double r = stod(match[4].str());
    size_t verCount = stoi(match[5].str());

    return std::make_shared<shapes::CPolygon>(color, x, y, r, verCount);
}

std::shared_ptr<shapes::CShape> MakeTriangle(const smatch &match) {
    string color = match[1].str();
    double x1 = stod(match[2].str());
    double y1 = stod(match[3].str());
    double x2 = stod(match[4].str());
    double y2 = stod(match[5].str());
    double x3 = stod(match[6].str());
    double y3 = stod(match[7].str());

    return std::make_shared<shapes::CTriangle>(color, x1, y1, x2, y2, x3, y3);
}

std::shared_ptr<shapes::CShape> CShapeFactory::CreateShape(const string &description) const {
    const string rectRegex =
            R"(^rectangle)" +
            reg::S + reg::COLOR + reg::S + reg::COORD + reg::S + reg::DIGIT + reg::S + reg::DIGIT +
            R"($)";
    const string ellipseRegex =
            R"(^ellipse)" +
            reg::S + reg::COLOR + reg::S + reg::COORD + reg::S + reg::DIGIT + reg::S + reg::DIGIT +
            R"($)";
    const string polygonRegex =
            R"(^polygon)" +
            reg::S + reg::COLOR + reg::S + reg::COORD + reg::S + reg::DIGIT + reg::S + reg::DIGIT +
            R"($)";
    const string triangleRegex =
            R"(^triangle)" +
            reg::S + reg::COLOR + reg::S + reg::COORD + reg::S + reg::COORD + reg::S + reg::COORD +
            R"($)";
    smatch match;
    if (regex_match(description, match, regex(rectRegex))) {
        return MakeRectangle(match);
    }
    if (regex_match(description, match, regex(ellipseRegex))) {
        return MakeEllipse(match);
    }
    if (regex_match(description, match, regex(polygonRegex))) {
        return MakePolygon(match);
    }
    if (regex_match(description, match, regex(triangleRegex))) {
        return MakeTriangle(match);
    }
    throw invalid_argument("Unknown shape type");
}