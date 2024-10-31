classDiagram
ICanvas <|.. CCanvas

    namespace graphics_lib {
        class ICanvas {
            + MoveTo(x int, y int)*
            + LineTo(x int, y int)*
        }

        class CCanvas {
            + MoveTo(x int, y int)
            + LineTo(x int, y int)
        }
    }

    namespace shape_drawing_lib {
        class Point {
            + x int
            + y int
        }

        class ICanvasDrawable {
            + Draw(canvas ICanvas)*
        }

        class CTriangle {
            + Draw(canvas ICanvas)
            - m_point1 Point
            - m_point2 Point
            - m_point3 Point
        }

        class CRectangle {
            + Draw(canvas ICanvas)
            - m_leftTop Point
            - m_width int
            - m_height int
        }

        class CanvasPainter {
            + Draw(drawable ICanvasDrawable)
            - m_canvas ICanvas
        }
    }

    modern_graphics_lib.Point <.. ModernGraphicsRenderer
    namespace modern_graphics_lib {

        class modern_graphics_lib.Point {
            + x int
            + y int
        }

        class ModernGraphicsRenderer {
            + BeginDraw()
            + DrawLine(start modern_graphics_lib.Point, end modern_graphics_lib.Point)
            + EndDraw()
            - m_out ostream
            - m_drawing bool
        }
    }

    namespace app {
        class ModernGraphicsAdapter {
            + MoveTo(x int, y int)
            + LineTo(x int, y int)
            - m_startPoint modern_graphics_lib.Point
            - m_renderer ModernGraphicsRenderer
        }
    }

    ICanvasDrawable <|.. CTriangle
    ICanvasDrawable <|.. CRectangle
    CTriangle o.. Point
    CRectangle o.. Point
    CanvasPainter o.. ICanvas
    ICanvasDrawable <.. CanvasPainter
    
    ICanvas <|.. ModernGraphicsAdapter
    ModernGraphicsAdapter o-- ModernGraphicsRenderer
    ModernGraphicsAdapter *-- modern_graphics_lib.Point