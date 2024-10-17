#include <fstream>
#include <gtest/gtest.h>
#include "../models/CShapeFactory.h"

TEST(ShapeFactoryTest, CreateTriangle)
{
    CShapeFactory factory;
    std::string description = "triangle #000000 0 0 1 0 0 1";
    std::shared_ptr<shapes::CShape> shape = factory.CreateShape(description);

    EXPECT_NE(shape, nullptr);
}

TEST(ShapeFactoryTest, CreateEllipse)
{
    CShapeFactory factory;
    std::string description = "ellipse #000000 0 0 5 3";
    std::shared_ptr<shapes::CShape> shape = factory.CreateShape(description);
    EXPECT_NE(shape, nullptr);
}

TEST(ShapeFactoryTest, CreateRectangle)
{
    CShapeFactory factory;
    std::string description = "rectangle #000000 0 0 3 4";
    std::shared_ptr<shapes::CShape> shape = factory.CreateShape(description);
    EXPECT_NE(shape, nullptr);
}

TEST(ShapeFactoryTest, CreateRegularPolygon)
{
    CShapeFactory factory;
    std::string description = "polygon #000000 0 0 5 6";
    std::shared_ptr<shapes::CShape> shape = factory.CreateShape(description);
    EXPECT_NE(shape, nullptr);
}

TEST(ShapeFactoryTest, InvalidShape) {
    CShapeFactory factory;
    std::string description = "unknown_shape #000000 0 0 1 1";
    EXPECT_THROW(factory.CreateShape(description), std::invalid_argument);
}