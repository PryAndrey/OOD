#include "../Libs/graphics_lib.h"
#include "../Libs/modern_graphics_lib.h"
#include "../ModernGraphicsClassAdapter.h"
#include <gtest/gtest.h>
#include <sstream>
#include <vector>

namespace mgl = modern_graphics_lib;
namespace gl = graphics_lib;

std::string DrawWithoutAdapter(const std::vector<mgl::Point>& points)
{
	std::stringstream strm;
	mgl::ModernGraphicsRenderer renderer(strm);

	const auto first = points.begin();
	renderer.BeginDraw();

	for (auto it = first; it != points.end(); ++it)
	{
		if (it + 1 != points.end())
		{
			renderer.DrawLine(*it, *(it + 1));
		}
		else
		{
			renderer.DrawLine(*it, *first);
		}
	}

	renderer.EndDraw();

	return strm.str();
}

void DrawWithAdapter(mgl::ModernGraphicsRenderer& renderer, graphics_lib::ICanvas& adapter, const std::vector<mgl::Point>& points)
{
	renderer.BeginDraw();

	auto first = points.begin();
	adapter.MoveTo((*first).x, (*first).y);

	for (auto it = first + 1; it != points.end(); ++it)
	{
		adapter.LineTo((*it).x, (*it).y);
	}

	adapter.LineTo((*first).x, (*first).y);
	renderer.EndDraw();
}

std::string DrawShapeWithClassAdapter(const std::vector<mgl::Point>& points)
{
	std::stringstream strm;
	app::ModernGraphicsClassAdapter adapter(strm);

	DrawWithAdapter(adapter, adapter, points);

	return strm.str();
}

TEST(ClassAdapterTest, InterfaceImplementation)
{
	std::stringstream strm;
	app::ModernGraphicsClassAdapter adapter(strm);

	graphics_lib::ICanvas* canvas = dynamic_cast<graphics_lib::ICanvas*>(&adapter);
	ASSERT_NE(canvas, nullptr);

	mgl::ModernGraphicsRenderer* renderer = dynamic_cast<mgl::ModernGraphicsRenderer*>(&adapter);
	ASSERT_NE(renderer, nullptr);
}

TEST(ClassAdapterTest, DrawWithClassAdapter)
{
	auto triangle = {
		mgl::Point(10, 15),
		mgl::Point(100, 200),
		mgl::Point(150, 250),
	};

	const auto originalShape = DrawWithoutAdapter(triangle);
	const auto withAdapterShape = DrawShapeWithClassAdapter(triangle);

	EXPECT_EQ(originalShape, withAdapterShape);
}

GTEST_API_ int main(int argc, char** argv)
{
	std::cout << "Running tests" << std::endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}