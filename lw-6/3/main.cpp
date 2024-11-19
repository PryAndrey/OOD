#include <iostream>
#include <string>

#include "Libs/graphics_lib.h"
#include "Libs/modern_graphics_lib.h"
#include "Libs/shape_drawing_lib.h"

#include "ModernGraphicsAdapter.h"

using namespace std;

namespace app
{
void PaintPicture(shape_drawing_lib::CanvasPainter& painter)
{
	using namespace shape_drawing_lib;

	const Triangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 }, 0xFF3401);
	const Rectangle rectangle({ 30, 40 }, 18, 24, 0xFF3456AA);

	painter.Draw(triangle);
	painter.Draw(rectangle);
}

void PaintPictureOnCanvas()
{
	graphics_lib::Canvas simpleCanvas;
	shape_drawing_lib::CanvasPainter painter(simpleCanvas);

	PaintPicture(painter);
}

void PaintPictureOnModernGraphicsRenderer()
{
	modern_graphics_lib::ModernGraphicsRenderer renderer(cout);
	app::ModernGraphicsAdapter modernGraphicsAdapter(renderer);
	shape_drawing_lib::CanvasPainter painter(modernGraphicsAdapter);

	renderer.BeginDraw();

	PaintPicture(painter);

	renderer.EndDraw();
}
} // namespace app

int main()
{
	cout << "Should we use new API (y)?";

	string userInput;

	if (getline(cin, userInput) && (userInput == "y" || userInput == "Y"))
	{
		app::PaintPictureOnModernGraphicsRenderer();
	}
	else
	{
		app::PaintPictureOnCanvas();
	}

	return 0;
}