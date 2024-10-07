#include "../models/Dance/IDanceBehavior.h"
#include "../models/Ducks/CDecoyDuck.cpp"
#include "../models/Ducks/CMallardDuck.cpp"
#include "../models/Ducks/CRedHeadDuck.cpp"
#include "../models/Ducks/CRubberDuck.cpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

using ::testing::_;
using ::testing::AnyNumber;
using ::testing::Invoke;

class MockWaltzDance : public IDanceBehavior
{
public:
	MOCK_METHOD(void, Dance, (), (override));
};
class MockMinuetDance : public IDanceBehavior
{
public:
	MOCK_METHOD(void, Dance, (), (override));
};

class MockNoDance : public IDanceBehavior
{
public:
	MOCK_METHOD(void, Dance, (), (override));
};

TEST(dance_test, dance_test)
{
	auto mockWaltzDance = std::make_unique<MockWaltzDance>();
	auto mockMinuetDance = std::make_unique<MockMinuetDance>();
	auto mockNoDance1 = std::make_unique<MockNoDance>();
	auto mockNoDance2 = std::make_unique<MockNoDance>();

	EXPECT_CALL(*mockWaltzDance, Dance())
		.Times(1)
		.WillOnce(Invoke([]() { std::cout << "Dance waltz" << std::endl; }));
	EXPECT_CALL(*mockMinuetDance, Dance())
		.Times(1)
		.WillOnce(Invoke([]() { std::cout << "Dance Minuet" << std::endl; }));
	EXPECT_CALL(*mockNoDance1, Dance())
		.Times(1)
		.WillOnce(Invoke([]() { std::cout << ". . ." << std::endl; }));
	EXPECT_CALL(*mockNoDance2, Dance())
		.Times(1)
		.WillOnce(Invoke([]() { std::cout << ". . ." << std::endl; }));

	CMallardDuck mDuck;
	mDuck.SetDanceBehavior(std::move(mockWaltzDance));

	CRedheadDuck rhDuck;
	rhDuck.SetDanceBehavior(std::move(mockMinuetDance));

	CDecoyDuck dDuck;
	dDuck.SetDanceBehavior(std::move(mockNoDance1));

	CRubberDuck rDuck;
	rDuck.SetDanceBehavior(std::move(mockNoDance2));

	mDuck.PerformDance();
	rhDuck.PerformDance();
	dDuck.PerformDance();
	rDuck.PerformDance();
}

int main(int argc, char** argv)
{
	::testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}