#include <iostream>
#include <string>

#include "Libs/graphics_lib.h"
#include "Libs/modern_graphics_lib.h"
#include "Libs/shape_drawing_lib.h"

#include "ModernGraphicsClassAdapter.h"

using namespace std;

namespace app
{
void PaintPicture(shape_drawing_lib::CCanvasPainter& painter)
{
	using namespace shape_drawing_lib;

	const CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 });
	const CRectangle rectangle({ 30, 40 }, 18, 24);

	painter.Draw(triangle);
	painter.Draw(rectangle);
}

void PaintPictureOnCanvas()
{
	graphics_lib::CCanvas simpleCanvas;
	shape_drawing_lib::CCanvasPainter painter(simpleCanvas);

	PaintPicture(painter);
}

void PaintPictureOnModernGraphicsRenderer()
{
	app::ModernGraphicsClassAdapter modernGraphicsAdapter(cout);
	shape_drawing_lib::CCanvasPainter painter(modernGraphicsAdapter);

	// todo Подумать над внесением begin draw в адаптер - done
	// todo добавить тест с нулевой позицией - done
	PaintPicture(painter);
}
}


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
