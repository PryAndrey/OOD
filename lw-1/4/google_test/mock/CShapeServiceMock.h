#pragma once

#include <fstream>
#include <functional>
#include <iostream>
#include <regex>
#include <vector>

#include "../../models/CCanvasSFML.h"
#include "../../models/Shapes/CCircle.h"
#include "../../models/Shapes/CLineSegment.h"
#include "../../models/Shapes/CRectangle.h"
#include "../../models/Shapes/CTriangle.h"
#include "../../models/Interface/ICanvas.h"
#include "../../models/CColor.h"
#include "../../models/CPoint.h"

using RegexPair = std::pair<std::regex, std::function<void(std::smatch match)>>;

class CShapeServiceMock
{
public:
	void ReadShapes(std::istream& inputStream);
	[[nodiscard]] ISolidShape* GetMaxAreaShape() const;
	[[nodiscard]] ISolidShape* GetMinPerimeterShape() const;
	void RenderShapes(std::ofstream& file);
	~CShapeServiceMock() = default;

private:
	std::vector<std::unique_ptr<ISolidShape>> m_shapes;
	std::vector<std::unique_ptr<ICanvasDrawable>> m_drawableShapes;

	void RectangleFabric(const std::smatch& match);
	void TriangleFabric(const std::smatch& match);
	void CircleFabric(const std::smatch& match);
	void LineFabric(const std::smatch& match);
	static CColor ColorFabric(const std::string& strColor, uint32_t templateColor);
	std::vector<RegexPair> GetRegexPairs();
};
