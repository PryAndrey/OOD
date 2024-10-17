#include "../models/CClient.h"
#include "mocks.h"
#include "../models/Shapes/Polygon/CPolygon.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(PainterTest, DrawPictureCallsDrawOnEachShape) {
    std::unique_ptr<gfx::ICanvas> canvas = make_unique<MockCanvas>();
    shapes::CPicture draft;
    auto shape1 = std::make_shared<MockShape>("FF0000");
    auto shape2 = std::make_shared<MockShape>("FF0000");

    MockShape *shapePtr1 = shape1.get();
    MockShape *shapePtr2 = shape2.get();

    draft.AddShape(std::move(shape1));
    draft.AddShape(std::move(shape2));

    CPainter painter;

    {
        testing::InSequence seq;
        EXPECT_CALL(*shapePtr1, Draw(::testing::Ref(canvas))).Times(1);
        EXPECT_CALL(*shapePtr2, Draw(::testing::Ref(canvas))).Times(1);
    }

    painter.DrawPicture(draft, canvas);
}
