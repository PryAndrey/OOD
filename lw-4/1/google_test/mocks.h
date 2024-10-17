#include "../models/CClient.h"
#include <fstream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class MockCanvas : public gfx::ICanvas {
public:
    MOCK_METHOD(void, SetColor, (const std::string& color), (override));
    MOCK_METHOD(void, DrawLine, (CPoint from, CPoint to), (override));
    MOCK_METHOD(void, DrawEllipse, (double cx, double cy, double rx, double ry), (override));
    MOCK_METHOD(void, Fill, (), (override));
};

class MockShape : public shapes::CShape {
public:
    MockShape(string color) : CShape(color) {}
    MOCK_METHOD(void, Draw, (std::unique_ptr<gfx::ICanvas> & canvas), (override, const));
    MOCK_METHOD(std::string, GetColor, ());
    MOCK_METHOD(std::string, GetType, (), (override, const));
    MOCK_METHOD(std::string, GetStringParams, (), (override, const));
};

class MockClient : public CClient {
public:
    MOCK_METHOD(void, HandleCommand,
                (std::istream & input, std::unique_ptr<gfx::ICanvas> & canvas, const CPainter &painter));
};

class MockPainter : public CPainter {
public:
    MOCK_METHOD(void, DrawPicture, (const shapes::CPicture &draft, std::unique_ptr<gfx::ICanvas> &canvas));
};

class MockPicture : public shapes::CPicture {
public:
    MOCK_METHOD(void, AddShape, (std::shared_ptr<shapes::CShape> shape));
    MOCK_METHOD(void, DeleteShape, (size_t index));
    MOCK_METHOD(std::shared_ptr<shapes::CShape>, GetShape, (size_t index));
    MOCK_METHOD(size_t, GetShapeCount, ());
    MOCK_METHOD(void, DrawPicture, (std::unique_ptr<gfx::ICanvas> & canvas));
};

class MockDesigner : public IDesigner {
public:
    MOCK_METHOD(shapes::CPicture, CreateDraft, (std::istream & strm));
};

class MockShapeFactory : public IShapeFactory {
public:
    MOCK_METHOD(std::shared_ptr<shapes::CShape>, CreateShape, (const string &description), (const override));
};