#include "../models/Ducks/CDecoyDuck.cpp"
#include "../models/Ducks/CMallardDuck.cpp"
#include "../models/Ducks/CRedHeadDuck.cpp"
#include "../models/Ducks/CRubberDuck.cpp"
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

TEST(dance_test, dance_test)
{
	ostringstream outputStream;
	streambuf* originalCoutBuffer = cout.rdbuf();
	cout.rdbuf(outputStream.rdbuf());

	CMallardDuck mDuck;
	mDuck.PerformDance();
	EXPECT_EQ(outputStream.str(), "Dance waltz\n");
	outputStream.str("");
	outputStream.clear();

	CRedheadDuck rhDuck;
	rhDuck.PerformDance();
	EXPECT_EQ(outputStream.str(), "Dance Minuet\n");
	outputStream.str("");
	outputStream.clear();

	CDecoyDuck dDuck;
	dDuck.PerformDance();
	EXPECT_EQ(outputStream.str(), ". . .\n");
	outputStream.str("");
	outputStream.clear();
	
	CRubberDuck rDuck;
	rDuck.PerformDance();
	EXPECT_EQ(outputStream.str(), ". . .\n");
	outputStream.str("");
	outputStream.clear();

	cout.rdbuf(originalCoutBuffer);
}

GTEST_API_ int main(int argc, char** argv)
{
	cout << "Running tests";
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
