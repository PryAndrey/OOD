#include "Canvas/SVGCanvas.h"
#include "Client.h"
#include "Shape/Factory/ShapeFactory.h"
#include <fstream>
#include <iostream>

const int WIDTH = 800;
const int HEIGHT = 800;

int main(int argc, char* argv[])
{
	try
	{
		gfx::CCanvasSVG canvas(WIDTH + 100, HEIGHT + 100);
		ShapeFactory shapeFactory;
		SlideService slideService(shapeFactory);
		Client client(slideService);

		if (argc != 2)
		{
			client.HandleCommand(std::cin, canvas, WIDTH, HEIGHT);
			canvas.SaveToFile("out.svg");
			return 0;
		}
		std::string inputFileName = argv[1];
		std::ifstream inputFile(inputFileName);

		if (!inputFile.is_open())
		{
			throw std::runtime_error("Failed to open input stream");
		}

		if (inputFile.peek() == std::ifstream::traits_type::eof())
		{
			throw std::runtime_error("Error reading input file: file is empty");
		}

		client.HandleCommand(inputFile, canvas, WIDTH, HEIGHT);
		canvas.SaveToFile("out.svg");
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}

// todo пустые группы в GetFrame в GroupShape - не хорошо
// todo переделать на шаблоны функции GroupStyles
// todo IStyleEnumerator по ссылке и функцией
// todo отделить коллекцию фигур от группы фигур в Slide
// todo тесты

/*

group_start
rectangle #FF00FF00 2 #35f0da 0 0 900 900
rectangle #FF00FF00 2 #35f05d 0 450 900 450
group_end

group_start
triangle #FF00FFFF 2 #E00420FF 50 10 200 200
rectangle #FF00FF 2 #D07440FF 50 210 200 200

group_start
rectangle #00000000 2 #AAAAAAFF 105 260 90 90
rectangle #00000000 2 #0040DDFF 107 262 42 42
rectangle #00000000 2 #0040DDFF 151 262 42 42
rectangle #00000000 2 #0040DDFF 107 306 42 42
rectangle #00000000 2 #0040DDFF 151 306 42 42
group_end

group_end
resizeFrame 50 210 200 400
ellipse #f0a535 2 #edf035 -100 -100 200 200

group_start
rectangle #FFFFFF 2 #bda03a 500 500 40 120
ellipse #3abd6f 2 #64bd3a 450 410 140 130
group_end
!

Можно добавить в любое место
setLineStyle #AAAAAA 7
setFillColor #D07440
resizeFrame 10 10 500 500

 */
