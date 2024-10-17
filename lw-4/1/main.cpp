#include "models/CClient.h"


int main()
{
    std::unique_ptr<gfx::ICanvas> canvas = std::make_unique<CCanvasSVG>(900, 900);
    std::shared_ptr<IShapeFactory> factory = std::make_shared<CShapeFactory>();
    std::shared_ptr<IDesigner> designer = std::make_shared<CDesigner>(factory);
    CPainter painter;
    CClient client(designer);
    client.HandleCommand(std::cin, canvas, painter);
	return 0;
}

/*
rectangle #991920 400 400 100 100
polygon #991920 300 300 50 10
triangle #991920 400 400 500 400 450 300
circle #991920 200 350 50
 как называются объекты производимые фабрикой
 разобраться в паттерне
 */