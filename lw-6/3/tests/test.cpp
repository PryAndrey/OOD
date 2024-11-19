#include "../Libs/graphics_lib.h"
#include "../Libs/modern_graphics_lib.h"
#include "../ModernGraphicsAdapter.h"
#include "../ModernGraphicsClassAdapter.h"
#include <gtest/gtest.h>
#include <sstream>
#include <vector>

namespace mgl = modern_graphics_lib;
namespace gl = graphics_lib;

mgl::RGBAColor ConvertColorHEXToRGBAColor(uint32_t rgbColor)
{
	float r, g, b, a = 0xFF;
	if (rgbColor > 0xFFFFFF)
	{
		r = ((rgbColor >> 24) & 0xFF) / 255.0f;
		g = ((rgbColor >> 16) & 0xFF) / 255.0f;
		b = ((rgbColor >> 8) & 0xFF) / 255.0f;
		a = (rgbColor & 0xFF) / 255.0f;
	}
	else
	{
		r = ((rgbColor >> 16) & 0xFF) / 255.0f;
		g = ((rgbColor >> 8) & 0xFF) / 255.0f;
		b = (rgbColor & 0xFF) / 255.0f;
	}

	mgl::RGBAColor color = { r, g, b, a };
	return color;
}

std::string DrawWithoutAdapter(const std::vector<mgl::Point>& points, uint32_t color)
{
	std::stringstream strm;
	mgl::ModernGraphicsRenderer renderer(strm);
	auto rgbaColor = ConvertColorHEXToRGBAColor(color);

	const auto first = points.begin();
	renderer.BeginDraw();

	for (auto it = first; it != points.end(); ++it)
	{
		if (it + 1 != points.end())
		{
			renderer.DrawLine(*it, *(it + 1), rgbaColor);
		}
		else
		{
			renderer.DrawLine(*it, *first, rgbaColor);
		}
	}

	renderer.EndDraw();

	return strm.str();
}

void DrawWithAdapter(mgl::ModernGraphicsRenderer& renderer, graphics_lib::ICanvas& adapter, const std::vector<mgl::Point>& points, uint32_t color)
{
	adapter.SetColor(color);
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

std::string DrawWithObjectAdapter(const std::vector<mgl::Point>& points, uint32_t color)
{
	std::stringstream strm;
	mgl::ModernGraphicsRenderer renderer(strm);
	app::ModernGraphicsAdapter adapter(renderer);

	DrawWithAdapter(renderer, adapter, points, color);

	return strm.str();
}

std::string DrawShapeWithClassAdapter(const std::vector<mgl::Point>& points, uint32_t color)
{
	std::stringstream strm;
	app::ModernGraphicsClassAdapter adapter(strm);

	DrawWithAdapter(adapter, adapter, points, color);

	return strm.str();
}

TEST(ObjectAdapterTest, InterfaceImplementation)
{
	std::stringstream strm;
	mgl::ModernGraphicsRenderer renderer(strm);
	app::ModernGraphicsAdapter adapter(renderer);

	graphics_lib::ICanvas* canvas = dynamic_cast<graphics_lib::ICanvas*>(&adapter);
	ASSERT_NE(canvas, nullptr);
}

TEST(ObjectAdapterTest, DrawWithObjectAdapter)
{
	auto triangle = {
		mgl::Point(10, 15),
		mgl::Point(100, 200),
		mgl::Point(150, 250),
	};

	uint32_t color = 0xFF5733FF;

	const auto originalShape = DrawWithoutAdapter(triangle, color);
	const auto withAdapterShape = DrawWithObjectAdapter(triangle, color);

	EXPECT_EQ(originalShape, withAdapterShape);
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

	uint32_t color = 0xFF5733FF;

	const auto originalShape = DrawWithoutAdapter(triangle, color);
	const auto withAdapterShape = DrawShapeWithClassAdapter(triangle, color);

	EXPECT_EQ(originalShape, withAdapterShape);
}

TEST(ClassAdapterTest, DrawWithClassAdapterBeginEndTest)
{
	std::stringstream strm;
	mgl::ModernGraphicsRenderer renderer(strm);

	auto rgbaColor = ConvertColorHEXToRGBAColor(0x000000);

	EXPECT_THROW(renderer.EndDraw(), std::logic_error);
	EXPECT_THROW(renderer.DrawLine(mgl::Point(0, 0), mgl::Point(0, 0), rgbaColor), std::logic_error);
	renderer.BeginDraw();
	EXPECT_THROW(renderer.BeginDraw(), std::logic_error);
	ASSERT_NO_THROW(renderer.DrawLine(mgl::Point(0, 0), mgl::Point(0, 0), rgbaColor));
	renderer.EndDraw();
	EXPECT_THROW(renderer.DrawLine(mgl::Point(0, 0), mgl::Point(0, 0), rgbaColor), std::logic_error);

}

GTEST_API_ int main(int argc, char** argv)
{
	std::cout << "Running tests" << std::endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}