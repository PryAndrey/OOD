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
/*

group_start
triangle #FF00FF 2 #E00420 50 10 200 200
rectangle #FF00FF 2 #D07440 50 210 200 200
rectangle #00FFFF 2 #4040D0 110 260 80 80
group_end
setLineStyle #AAAAAA 40
setFillColor #000FFF
ellipse #0014A0 2 #d897aF 260 50 200 200
!

resizeFrame 10 10 500 500
resizeFrame 10 10 20 20

 */
