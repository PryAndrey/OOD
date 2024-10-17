#pragma once

#include "Designer/CDesigner.h"
#include "CPainter.h"
#include <iostream>
#include <regex>
#include <string>

class CClient {
public:
    explicit CClient(std::shared_ptr<IDesigner> &designer) : m_designer(designer) {};

    void HandleCommand(std::istream &input, std::unique_ptr<gfx::ICanvas>& canvas, const CPainter &painter) {
        shapes::CPicture draft = m_designer->CreateDraft(input);
        painter.DrawPicture(draft, canvas);
    }
private:
    std::shared_ptr<IDesigner> &m_designer;
};
