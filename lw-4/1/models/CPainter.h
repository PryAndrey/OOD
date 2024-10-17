#pragma once

#include "Picture/CPicture.h"
#include "Canvas/CCanvas.h"

class CPainter {
public:
    static void DrawPicture(const shapes::CPicture &draft, std::unique_ptr<gfx::ICanvas> &canvas) {
        draft.DrawPicture(canvas);
    }
};
