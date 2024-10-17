#include "../models/CClient.h"
#include "mocks.h"
#include "../models/Shapes/Polygon/CPolygon.h"
#include "../models/Shapes/Ellipse/CEllipse.h"
#include "../models/Shapes/Triangle/CTriangle.h"
#include "../models/Shapes/Rectangle/CRectangle.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(Ellipse, IsBeingCreated) {
    shapes::CEllipse ellipse("000000", 0, 0, 10, 10);

    EXPECT_EQ(ellipse.GetColor(), "#000000");
    EXPECT_EQ(ellipse.GetCenter(), CPoint(0, 0));
    EXPECT_EQ(ellipse.GetHorizontalRadius(), 10);
    EXPECT_EQ(ellipse.GetVerticalRadius(), 10);
}

TEST(Ellipse, IsBeingDrawn) {
    MockCanvas *mockCanvasPtr = new MockCanvas();
    std::unique_ptr<gfx::ICanvas> mockCanvas(mockCanvasPtr);
    shapes::CEllipse ellipse("000000", 0, 0, 10, 10);

    EXPECT_CALL(*mockCanvasPtr, SetColor("000000")).Times(1);
    EXPECT_CALL(*mockCanvasPtr, DrawEllipse(0, 0, 10, 10)).Times(1);

    ellipse.Draw(mockCanvas);
}

TEST(Rectangle, IsBeingCreated) {
    shapes::CRectangle rectangle("000000", 5, 5, 10, 10);

    EXPECT_EQ(rectangle.GetColor(), "#000000");
    EXPECT_TRUE(rectangle.GetLeftTop() == CPoint(5, 5));
    EXPECT_TRUE(rectangle.GetRightBottom() == CPoint(15, 15));
}

TEST(Rectangle, IsBeingDrawn) {
    MockCanvas *mockCanvasPtr = new MockCanvas();
    std::unique_ptr<gfx::ICanvas> mockCanvas(mockCanvasPtr);
    shapes::CRectangle rectangle("000000", 5, 5, 10, 10);

    EXPECT_CALL(*mockCanvasPtr, SetColor("000000")).Times(1);
    EXPECT_CALL(*mockCanvasPtr, DrawLine(CPoint(5, 5), CPoint(15, 5))).Times(1);
    EXPECT_CALL(*mockCanvasPtr, DrawLine(CPoint(15, 5), CPoint(15, 15))).Times(1);
    EXPECT_CALL(*mockCanvasPtr, DrawLine(CPoint(15, 15), CPoint(5, 15))).Times(1);
    EXPECT_CALL(*mockCanvasPtr, DrawLine(CPoint(5, 15), CPoint(5, 5))).Times(1);
    EXPECT_CALL(*mockCanvasPtr, Fill()).Times(1);

    rectangle.Draw(mockCanvas);
}

TEST(RegularPolygon, IsBeingCreated) {
    shapes::CPolygon polygon("000000", 0, 0, 10, 5);

    EXPECT_EQ(polygon.GetColor(), "#000000");
    EXPECT_TRUE(polygon.GetCenter() == CPoint(0, 0));
    EXPECT_EQ(polygon.GetRadius(), 10);
    EXPECT_EQ(polygon.GetVertexCount(), 5);
}

TEST(ExceptionTest, ThrowsOnInvalidData) {
    EXPECT_THROW(shapes::CPolygon("000000", 0, 0, 10, 2), std::invalid_argument);
    EXPECT_THROW(shapes::CEllipse("000000", 0, 0, 0, -1), std::invalid_argument);
    EXPECT_THROW(shapes::CRectangle("000000", 0, 0, -1, -1), std::invalid_argument);
    EXPECT_NO_THROW(shapes::CTriangle("000000", 0, 0, 1, 1, 1, 1));
}

TEST(RegularPolygon, IsBeingDrawn) {
    MockCanvas *mockCanvasPtr = new MockCanvas();
    std::unique_ptr<gfx::ICanvas> mockCanvas(mockCanvasPtr);
    shapes::CPolygon polygon("000000", 0, 0, 10, 3);

    EXPECT_CALL(*mockCanvasPtr, SetColor("000000")).Times(1);
    EXPECT_CALL(*mockCanvasPtr, Fill()).Times(1);

    const double angleIncrement = 2 * M_PI / 3;
    std::vector<CPoint> expectedVertices;
    for (int i = 0; i < 3; ++i) {
        double angle = i * angleIncrement;
        double x = (0 + 10 * cos(angle));
        double y = (0 + 10 * sin(angle));
        expectedVertices.emplace_back(x, y);
    }

    for (int i = 0; i < 3; ++i) {
        const CPoint &from = expectedVertices[i];
        const CPoint &to = expectedVertices[(i + 1) % 3];
        EXPECT_CALL(*mockCanvasPtr, DrawLine(from, to)).Times(1);
    }

    polygon.Draw(mockCanvas);
}

TEST(Triangle, IsBeingCreated) {
    shapes::CTriangle triangle("000000", 5, 0, 10, 10, 0, 10);

    EXPECT_EQ(triangle.GetColor(), "#000000");
    EXPECT_TRUE(triangle.GetVertex1() == CPoint(5, 0));
    EXPECT_TRUE(triangle.GetVertex2() == CPoint(10, 10));
    EXPECT_TRUE(triangle.GetVertex3() == CPoint(0, 10));
}

TEST(Triangle, IsBeingDrawn) {
    MockCanvas *mockCanvasPtr = new MockCanvas();
    std::unique_ptr<gfx::ICanvas> mockCanvas(mockCanvasPtr);
    shapes::CTriangle triangle("000000", 5, 0, 10, 10, 0, 10);

    EXPECT_CALL(*mockCanvasPtr, SetColor("000000")).Times(1);
    EXPECT_CALL(*mockCanvasPtr, DrawLine(CPoint(5, 0), CPoint(10, 10))).Times(1);
    EXPECT_CALL(*mockCanvasPtr, DrawLine(CPoint(10, 10), CPoint(0, 10))).Times(1);
    EXPECT_CALL(*mockCanvasPtr, DrawLine(CPoint(0, 10), CPoint(5, 0))).Times(1);
    EXPECT_CALL(*mockCanvasPtr, Fill()).Times(1);

    triangle.Draw(mockCanvas);
}
