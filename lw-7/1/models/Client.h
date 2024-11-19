#pragma once

#include "Canvas/ICanvas.h"
#include "Slide/SlideService.h"

class Client
{
public:
    explicit Client(SlideService & slideService)
        : m_slideService(slideService)
    {}

    void HandleCommand(std::istream & inputData, gfx::ICanvas & canvas, double width, double height)
    {
        m_slideService.CreateSlide(inputData, width, height);
        m_slideService.DrawSlide(canvas);
    }

private:
    SlideService & m_slideService;
};
