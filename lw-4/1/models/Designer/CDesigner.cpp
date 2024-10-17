

#include "../Picture/CPicture.h"
#include "../CShapeFactory.h"
#include "CDesigner.h"

shapes::CPicture CDesigner::CreateDraft(std::istream &strm) {
    shapes::CPicture picture;
    std::string line;
    while (getline(strm, line)) {
        if (line == "!") {
            break;
        }
        try {
            std::shared_ptr<shapes::CShape> shape = m_shapeFactory->CreateShape(line);
            picture.AddShape(shape);
        } catch (std::exception &e) {
            cout << e.what() << endl;
        }
    }
    return picture;
}

