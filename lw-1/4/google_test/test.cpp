#include "../../4/models/Shapes/ShapesStrategy/IShapeType.h"
#include "../models/Picture/CPicture.cpp"
#include "../models/Shapes/ShapesStrategy/Circle/CCircleShapeType.cpp"
#include "../models/Shapes/ShapesStrategy/Line/CLineShapeType.cpp"
#include "../models/Shapes/ShapesStrategy/Rectangle/CRectangleShapeType.cpp"
#include "../models/Shapes/ShapesStrategy/Text/CTextShapeType.cpp"
#include "../models/Shapes/ShapesStrategy/Triangle/CTriangleShapeType.cpp"
#include "ICanvas.h"
#include <fstream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class MockCanvas : public gfx::ICanvas
{
public:
	MOCK_METHOD(void, SetColor, (const std::string& color), (override));
	MOCK_METHOD(void, MoveTo, (double x, double y), (override));
	MOCK_METHOD(void, LineTo, (double x, double y), (override));
	MOCK_METHOD(void, DrawEllipse, (double cx, double cy, double rx, double ry), (override));
	MOCK_METHOD(void, DrawText, (double left, double top, double fontSize, const std::string& text), (override));
	MOCK_METHOD(void, Fill, (), (override));
};

TEST(PictureTest, AddShapeTest)
{
	shapes::CPicture picture;

	std::unique_ptr<shapes::IShapeType> rect(new shapes::CRectangleShapeType(100, 100, 200, 200));
	std::unique_ptr<shapes::CShape> sh1 = std::make_unique<shapes::CShape>("sh1", "f0f0f0", std::move(rect));

	picture.AddShape("sh1", std::move(sh1));

	EXPECT_EQ(picture.GetShapeById("sh1"), "rectangle sh1 #f0f0f0 100 100 200 200");
}

TEST(PictureTest, ChangeShapeTest)
{
	shapes::CPicture picture;

	std::unique_ptr<shapes::IShapeType> rect(new shapes::CRectangleShapeType(100, 100, 200, 200));
	std::unique_ptr<shapes::CShape> sh1 = std::make_unique<shapes::CShape>("sh1", "f0f0f0", std::move(rect));

	picture.AddShape("sh1", std::move(sh1));

	std::unique_ptr<shapes::IShapeType> newShapeType(new shapes::CCircleShapeType(100, 100, 200));
	picture.ChangeShape("sh1", std::move(newShapeType));

	EXPECT_EQ(picture.GetShapeById("sh1"), "circle sh1 #f0f0f0 100 100 200");
}

TEST(PictureTest, MoveShapeTest)
{
	shapes::CPicture picture;

	std::unique_ptr<shapes::IShapeType> rect(new shapes::CRectangleShapeType(100, 100, 200, 200));
	std::unique_ptr<shapes::CShape> sh1 = std::make_unique<shapes::CShape>("sh1", "f0f0f0", std::move(rect));

	picture.AddShape("sh1", std::move(sh1));

	picture.MoveShape("sh1", 100, 100);

	EXPECT_EQ(picture.GetShapeById("sh1"), "rectangle sh1 #f0f0f0 200 200 200 200");
}

TEST(PictureTest, MovePictureTest)
{
	shapes::CPicture picture;

	std::unique_ptr<shapes::IShapeType> rect(new shapes::CRectangleShapeType(100, 100, 200, 200));
	std::unique_ptr<shapes::CShape> sh1 = std::make_unique<shapes::CShape>("sh1", "f0f0f0", std::move(rect));
	picture.AddShape("sh1", std::move(sh1));
	std::unique_ptr<shapes::IShapeType> circle(new shapes::CCircleShapeType(100, 100, 200));
	std::unique_ptr<shapes::CShape> sh2 = std::make_unique<shapes::CShape>("sh2", "f0f0f0", std::move(circle));
	picture.AddShape("sh2", std::move(sh2));

	picture.MovePicture(100, 100);

	EXPECT_EQ(picture.GetShapeById("sh1"), "rectangle sh1 #f0f0f0 200 200 200 200");
	EXPECT_EQ(picture.GetShapeById("sh2"), "circle sh2 #f0f0f0 200 200 200");
}

TEST(PictureTest, DeleteShapeTest)
{
	shapes::CPicture picture;

	std::unique_ptr<shapes::IShapeType> rect(new shapes::CRectangleShapeType(100, 100, 200, 200));
	std::unique_ptr<shapes::CShape> sh1 = std::make_unique<shapes::CShape>("sh1", "f0f0f0", std::move(rect));
	picture.AddShape("sh1", std::move(sh1));

	picture.DeleteShape("sh1");
	EXPECT_THROW(picture.GetShapeById("sh1"), std::invalid_argument);
}

TEST(PictureTest, ChangeColorTest)
{
	shapes::CPicture picture;

	std::unique_ptr<shapes::IShapeType> rect(new shapes::CRectangleShapeType(100, 100, 200, 200));
	std::unique_ptr<shapes::CShape> sh1 = std::make_unique<shapes::CShape>("sh1", "f0f0f0", std::move(rect));
	picture.AddShape("sh1", std::move(sh1));

	picture.ChangeColor("sh1", "000000");

	EXPECT_EQ(picture.GetShapeById("sh1"), "rectangle sh1 #000000 100 100 200 200");
}

TEST(ShapeTest, RectangleTest)
{
	MockCanvas mockCanvas;
	std::unique_ptr<shapes::IShapeType> rect(new shapes::CRectangleShapeType(100, 100, 200, 200));
	std::unique_ptr<shapes::CShape> sh1 = std::make_unique<shapes::CShape>("sh1", "f0f0f0", std::move(rect));

	EXPECT_CALL(mockCanvas, SetColor("f0f0f0"));
	EXPECT_CALL(mockCanvas, MoveTo(100, 100));
	EXPECT_CALL(mockCanvas, LineTo(300, 100));
	EXPECT_CALL(mockCanvas, LineTo(300, 300));
	EXPECT_CALL(mockCanvas, LineTo(100, 300));
	EXPECT_CALL(mockCanvas, LineTo(100, 100));
	EXPECT_CALL(mockCanvas, Fill());

	sh1->Draw(mockCanvas);
	sh1->Move(100, -50);

	EXPECT_EQ(sh1->GetStringParams(), "200 50 200 200");

	EXPECT_THROW(new shapes::CRectangleShapeType(100, 100, -100, -100), std::invalid_argument);
}

TEST(ShapeTest, CircleTest)
{
	MockCanvas mockCanvas;
	std::unique_ptr<shapes::IShapeType> circle(new shapes::CCircleShapeType(100, 100, 200));
	std::unique_ptr<shapes::CShape> sh1 = std::make_unique<shapes::CShape>("sh1", "f0f0f0", std::move(circle));

	EXPECT_CALL(mockCanvas, SetColor("f0f0f0"));
	EXPECT_CALL(mockCanvas, DrawEllipse(100, 100, 200, 200));

	sh1->Draw(mockCanvas);
	sh1->Move(100, -50);

	EXPECT_EQ(sh1->GetStringParams(), "200 50 200");

	EXPECT_THROW(new shapes::CCircleShapeType(100, 100, -100), std::invalid_argument);
}

TEST(ShapeTest, TriangleTest)
{
	MockCanvas mockCanvas;
	std::unique_ptr<shapes::IShapeType> triangle(new shapes::CTriangleShapeType(100, 100, 200, 100, 100, 200));
	std::unique_ptr<shapes::CShape> sh1 = std::make_unique<shapes::CShape>("sh1", "f0f0f0", std::move(triangle));

	EXPECT_CALL(mockCanvas, SetColor("f0f0f0"));
	EXPECT_CALL(mockCanvas, MoveTo(100, 100));
	EXPECT_CALL(mockCanvas, LineTo(200, 100));
	EXPECT_CALL(mockCanvas, LineTo(100, 200));
	EXPECT_CALL(mockCanvas, LineTo(100, 100));
	EXPECT_CALL(mockCanvas, Fill());

	sh1->Draw(mockCanvas);
	sh1->Move(100, -50);

	EXPECT_EQ(sh1->GetStringParams(), "200 50 300 50 200 150");
}

TEST(ShapeTest, LineTest)
{
	MockCanvas mockCanvas;
	std::unique_ptr<shapes::IShapeType> triangle(new shapes::CLineShapeType(100, 100, 200, 200));
	std::unique_ptr<shapes::CShape> sh1 = std::make_unique<shapes::CShape>("sh1", "f0f0f0", std::move(triangle));

	EXPECT_CALL(mockCanvas, SetColor("f0f0f0"));
	EXPECT_CALL(mockCanvas, MoveTo(100, 100));
	EXPECT_CALL(mockCanvas, LineTo(200, 200));
	EXPECT_CALL(mockCanvas, Fill());

	sh1->Draw(mockCanvas);
	sh1->Move(100, -50);

	EXPECT_EQ(sh1->GetStringParams(), "200 50 300 150");
}

TEST(ShapeTest, TextTest)
{
	MockCanvas mockCanvas;
	std::unique_ptr<shapes::IShapeType> triangle(new shapes::CTextShapeType(100, 100, 20, "Hello world"));
	std::unique_ptr<shapes::CShape> sh1 = std::make_unique<shapes::CShape>("sh1", "f0f0f0", std::move(triangle));

	EXPECT_CALL(mockCanvas, SetColor("f0f0f0"));
	EXPECT_CALL(mockCanvas, DrawText(100, 100, 20, "Hello world"));

	sh1->Draw(mockCanvas);
	sh1->Move(100, -50);

	EXPECT_EQ(sh1->GetStringParams(), "200 50 20 Hello world");

	EXPECT_THROW(new shapes::CTextShapeType(100, 100, -20, "Hello world"), std::invalid_argument);
}

GTEST_API_ int main(int argc, char** argv)
{
	std::cout << "Running tests";
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
