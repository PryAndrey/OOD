#include "CShapeService.h"

using namespace std;

int main()
{
	ifstream file("../../4/test1.txt");
	if (!file.is_open())
	{
		cout << "Can`t open inputFile" << endl;
		return 0;
	}
	CShapeService shapeService;
	shapeService.ReadShapes(file);
	ISolidShape* areaShape = shapeService.GetMaxAreaShape();
	ISolidShape* perimeterShape = shapeService.GetMinPerimeterShape();
	if (areaShape == nullptr)
	{
		cout << "Empty shapes" << endl;
		return 0;
	}
	cout << "Shape with min perimeter: " << endl
		 << perimeterShape->ToString() << endl;
	cout << "Shape with max area: " << endl
		 << areaShape->ToString() << endl;
	shapeService.RenderShapes();
	return 0;
}//вынести
