#pragma once

#include "../Picture/CPicture.h"
#include "../CShapeFactory.h"
#include <iostream>
#include <regex>
#include <string>

class IDesigner {
public:
    virtual shapes::CPicture CreateDraft(std::istream &strm) = 0; // заполняет макет
    virtual ~IDesigner() = default;
};

class CDesigner : public IDesigner {
public:
    explicit CDesigner(std::shared_ptr<IShapeFactory> factory)
            : m_shapeFactory(std::move(factory)) {};

    // заполняет макет
    shapes::CPicture CreateDraft(std::istream &strm) override;

private:
    std::shared_ptr<IShapeFactory> m_shapeFactory;
};
