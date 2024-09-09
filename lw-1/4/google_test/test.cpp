#include "../CShapeService.h"
#include "fakeit.hpp"
#include "mock/CShapeServiceMock.h"
#include <fstream>
#include <gtest/gtest.h>
using namespace std;

TEST(empty_test, empty_test)
{
	ifstream file("../../4/google_test/testFiles/testE.txt");
	if (!file.is_open())
	{
		cout << "Can`t open inputFile" << endl;
	}
	CShapeService shapeService;
	shapeService.ReadShapes(file);
	ISolidShape* areaShape = shapeService.GetMaxAreaShape();
	EXPECT_TRUE(areaShape == nullptr);
}

TEST(create_test, create_rectangle_test)
{
	ifstream file("../../4/google_test/testFiles/test1.txt");
	if (!file.is_open())
	{
		cout << "Can`t open inputFile" << endl;
	}
	CShapeService shapeService;
	shapeService.ReadShapes(file);
	ISolidShape* areaShape = shapeService.GetMaxAreaShape();
	string expectedString = "Rectangle: \n"
							"TopLeftPoint: (X: 10.00, Y: 10.00)\n"
							"Width: 12.00\n"
							"Height: 12.00\n"
							"OutlineColor: fe0fa0ff\n"
							"FillColor: ffffffff\n"
							"Area: 144.00\n"
							"Perimeter: 48.00\n";
	EXPECT_EQ(areaShape->ToString(), expectedString);
}

TEST(create_test, create_triangle_test)
{
	ifstream file("../../4/google_test/testFiles/test2.txt");
	if (!file.is_open())
	{
		cout << "Can`t open inputFile" << endl;
	}
	CShapeService shapeService;
	shapeService.ReadShapes(file);
	ISolidShape* areaShape = shapeService.GetMaxAreaShape();
	string expectedString = "Triangle: \n"
							"Point1: (X: 10.00, Y: 10.00)\n"
							"Point2: (X: 10.00, Y: 20.00)\n"
							"Point3: (X: 20.00, Y: 10.00)\n"
							"OutlineColor: fe0fa0ff\n"
							"FillColor: ffffffff\n"
							"Area: 50.00\n"
							"Perimeter: 34.14\n";
	EXPECT_EQ(areaShape->ToString(), expectedString);
}

TEST(create_test, create_circle_test)
{
	ifstream file("../../4/google_test/testFiles/test3.txt");
	if (!file.is_open())
	{
		cout << "Can`t open inputFile" << endl;
	}
	CShapeService shapeService;
	shapeService.ReadShapes(file);
	ISolidShape* areaShape = shapeService.GetMaxAreaShape();
	string expectedString = "Circle: \n"
							"Point: (X: 10.00, Y: 10.00)\n"
							"Radius: 5.00\n"
							"OutlineColor: fe0fa0ff\n"
							"FillColor: ffffffff\n"
							"Area: 78.54\n"
							"Perimeter: 31.42\n";
	EXPECT_EQ(areaShape->ToString(), expectedString);
}

TEST(min_perimeter_test, min_perimeter_rectangle_test)
{
	ifstream file("../../4/google_test/testFiles/testP1.txt");
	if (!file.is_open())
	{
		cout << "Can`t open inputFile" << endl;
	}
	CShapeService shapeService;
	shapeService.ReadShapes(file);
	ISolidShape* perimeterShape = shapeService.GetMinPerimeterShape();
	string expectedString = "Rectangle: \n"
							"TopLeftPoint: (X: 10.00, Y: 10.00)\n"
							"Width: 5.00\n"
							"Height: 5.00\n"
							"OutlineColor: fe0fa0ff\n"
							"FillColor: ffffffff\n"
							"Area: 25.00\n"
							"Perimeter: 20.00\n";
	EXPECT_EQ(perimeterShape->ToString(), expectedString);
}

TEST(min_perimeter_test, min_perimeter_triangle_test)
{
	ifstream file("../../4/google_test/testFiles/testP2.txt");
	if (!file.is_open())
	{
		cout << "Can`t open inputFile" << endl;
	}
	CShapeService shapeService;
	shapeService.ReadShapes(file);
	ISolidShape* perimeterShape = shapeService.GetMinPerimeterShape();
	string expectedString = "Triangle: \n"
							"Point1: (X: 0.00, Y: 0.00)\n"
							"Point2: (X: 0.00, Y: 10.00)\n"
							"Point3: (X: 10.00, Y: 0.00)\n"
							"OutlineColor: fe0fa0ff\n"
							"FillColor: ffffffff\n"
							"Area: 50.00\n"
							"Perimeter: 34.14\n";
	EXPECT_EQ(perimeterShape->ToString(), expectedString);
}

TEST(min_perimeter_test, min_perimeter_circle_test)
{
	ifstream file("../../4/google_test/testFiles/testP3.txt");
	if (!file.is_open())
	{
		cout << "Can`t open inputFile" << endl;
	}
	CShapeService shapeService;
	shapeService.ReadShapes(file);
	ISolidShape* perimeterShape = shapeService.GetMinPerimeterShape();
	string expectedString = "Circle: \n"
							"Point: (X: 10.00, Y: 10.00)\n"
							"Radius: 5.00\n"
							"OutlineColor: fe0fa0ff\n"
							"FillColor: ffffffff\n"
							"Area: 78.54\n"
							"Perimeter: 31.42\n";
	EXPECT_EQ(perimeterShape->ToString(), expectedString);
}

TEST(max_area_test, max_area_rectangle_test)
{
	ifstream file("../../4/google_test/testFiles/testA1.txt");
	if (!file.is_open())
	{
		cout << "Can`t open inputFile" << endl;
	}
	CShapeService shapeService;
	shapeService.ReadShapes(file);
	ISolidShape* areaShape = shapeService.GetMaxAreaShape();
	string expectedString = "Rectangle: \n"
							"TopLeftPoint: (X: 10.00, Y: 10.00)\n"
							"Width: 30.00\n"
							"Height: 30.00\n"
							"OutlineColor: fe0fa0ff\n"
							"FillColor: ffffffff\n"
							"Area: 900.00\n"
							"Perimeter: 120.00\n";
	EXPECT_EQ(areaShape->ToString(), expectedString);
}

TEST(max_area_test, max_area_triangle_test)
{
	ifstream file("../../4/google_test/testFiles/testA2.txt");
	if (!file.is_open())
	{
		cout << "Can`t open inputFile" << endl;
	}
	CShapeService shapeService;
	shapeService.ReadShapes(file);
	ISolidShape* areaShape = shapeService.GetMaxAreaShape();
	string expectedString = "Triangle: \n"
							"Point1: (X: 0.00, Y: 0.00)\n"
							"Point2: (X: 0.00, Y: 50.00)\n"
							"Point3: (X: 50.00, Y: 0.00)\n"
							"OutlineColor: fe0fa0ff\n"
							"FillColor: ffffffff\n"
							"Area: 1250.00\n"
							"Perimeter: 170.71\n";
	EXPECT_EQ(areaShape->ToString(), expectedString);
}

TEST(max_area_test, max_area_circle_test)
{
	ifstream file("../../4/google_test/testFiles/testA3.txt");
	if (!file.is_open())
	{
		cout << "Can`t open inputFile" << endl;
	}
	CShapeService shapeService;
	shapeService.ReadShapes(file);
	ISolidShape* areaShape = shapeService.GetMaxAreaShape();
	string expectedString = "Circle: \n"
							"Point: (X: 10.00, Y: 10.00)\n"
							"Radius: 25.00\n"
							"OutlineColor: fe0fa0ff\n"
							"FillColor: ffffffff\n"
							"Area: 1963.50\n"
							"Perimeter: 157.08\n";
	EXPECT_EQ(areaShape->ToString(), expectedString);
}

TEST(render_test, render_test)
{
	ifstream file("../../4/google_test/testFiles/testR.txt");
	if (!file.is_open())
	{
		cout << "Can`t open inputFile" << endl;
	}
	CShapeServiceMock shapeService;
	shapeService.ReadShapes(file);

	ofstream temp("../../4/google_test/temp.txt");
	shapeService.RenderShapes(temp);
	temp.close();

	ifstream logs("../../4/google_test/temp.txt");
	ifstream tempResult("../../4/google_test/tempResult1.txt");
	if (!logs.is_open() || !tempResult.is_open())
	{
		cout << "Can`t open file" << endl;
		return;
	}
	string line1, line2;
	while (logs.eof())
	{
		getline(logs, line1);
		getline(tempResult, line2);
		EXPECT_EQ(line1, line2);
	}
}
//test double output

GTEST_API_ int main(int argc, char** argv)
{
	cout << "Running tests";
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
