#pragma once

#include "Picture/CPicture.h"
#include <iostream>
#include <regex>
#include <string>

namespace reg {
    const std::string ID = R"(([\w\d]+))";
    const std::string S = R"(\s+)";
    const std::string DIGIT = R"((-?\d+(?:\.\d+)?))";
    const std::string COORD = DIGIT + S + DIGIT;
    const std::string COLOR = R"(#([0-9A-Fa-f]{6}))";
}; // namespace reg

using namespace std;

class IShapeFactory {
public:
    [[nodiscard]] virtual std::shared_ptr<shapes::CShape> CreateShape(const string &description) const = 0;
    virtual ~IShapeFactory() = default;
};

class CShapeFactory : public IShapeFactory {
public:
    [[nodiscard]] std::shared_ptr<shapes::CShape> CreateShape(const string &description) const override;
};
