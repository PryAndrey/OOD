#include "../models/CClient.h"
#include "mocks.h"

#include <fstream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(ClientTest, HandleCommand) {
    unique_ptr<gfx::ICanvas> mockCanvas = make_unique<MockCanvas>();
    shapes::CPicture draft;
    MockPainter mockPainter;
    MockDesigner* mockDesignerPtr = new MockDesigner();
    std::shared_ptr<IDesigner> mockDesigner(mockDesignerPtr);

    EXPECT_CALL(*mockDesignerPtr, CreateDraft(testing::_)).Times(1);
//    EXPECT_CALL(mockPainter, DrawPicture(testing::_, testing::_)).Times(1);
    CClient client(mockDesigner);

    std::istringstream inputData("rectangle #000000 0 0 10 10\nrectangle #000000 0 0 10 10\nrectangle #000000 0 0 10 10\n");

    client.HandleCommand(inputData, mockCanvas, mockPainter);
}