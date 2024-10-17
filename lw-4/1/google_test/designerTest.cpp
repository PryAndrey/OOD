#include "../models/CClient.h"
#include "mocks.h"
#include "../models/Shapes/Polygon/CPolygon.h"
#include "../models/Shapes/Ellipse/CEllipse.h"
#include "../models/Shapes/Triangle/CTriangle.h"
#include <fstream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(DesignerTest, CreateDraft) {

    MockShapeFactory *mockFactoryPtr = new MockShapeFactory();
    std::shared_ptr<IShapeFactory> mockShapeFactory(mockFactoryPtr);

    EXPECT_CALL(*mockFactoryPtr, CreateShape("shape1")).WillOnce(
            testing::Return(std::make_shared<shapes::CPolygon>("FF0000", 0, 0, 5, 5)));
    EXPECT_CALL(*mockFactoryPtr, CreateShape("shape2")).WillOnce(
            testing::Return(std::make_shared<shapes::CEllipse>("00FF00", 0, 0, 5, 10)));
    EXPECT_CALL(*mockFactoryPtr, CreateShape("shape3")).WillOnce(
            testing::Return(std::make_shared<shapes::CTriangle>("0000FF", 0, 0, 5, 0, 0, 5)));

    CDesigner designer(mockShapeFactory);

    std::istringstream inputData("shape1\nshape2\nshape3\n");

    shapes::CPicture draft = designer.CreateDraft(inputData);

    EXPECT_EQ(draft.GetShapeCount(), 3);

    EXPECT_EQ(draft.GetShape(0)->GetColor(), "#FF0000");
    EXPECT_EQ(draft.GetShape(1)->GetColor(), "#00FF00");
    EXPECT_EQ(draft.GetShape(2)->GetColor(), "#0000FF");
}
