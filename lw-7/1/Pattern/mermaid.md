classDiagram
class Client {
+Client(SlideService &slideService)
+HandleCommand(std::istream &inputData, gfx::ICanvas &canvas, double width, double height)
-SlideService &m_slideService
}

    class SlideService {
        +SlideService(IShapeFactory &shapeFactory)
        +CreateSlide(std::istream &inputData, double width, double height)
        +DrawSlide(gfx::ICanvas &canvas)
        -IShapeFactory &m_shapeFactory
        -std::unique_ptr<ISlide> m_currentSlide
    }

    class IShapeFactory {
        <<interface>>
        +CreateShape(const std::string &description) : std::shared_ptr<IShape>
    }

    class ShapeFactory {
        +CreateShape(const std::string &description) : std::shared_ptr<IShape>
    }

    class ISlide {
        <<interface>>
        +GetWidth() : double
        +GetHeight() : double
        +GetShapeAtIndex(size_t index) : std::shared_ptr<IShape>
        +InsertShape(const std::shared_ptr<IShape> &shape, size_t index)
        +RemoveShapeAtIndex(size_t index)
    }

    class Slide {
        +Slide(double width, double height, std::shared_ptr<GroupShape> shapes)
        +GetWidth() : double
        +GetHeight() : double
        +InsertShape(const std::shared_ptr<IShape> &shape, size_t index)
        +RemoveShapeAtIndex(size_t index)
        +Draw(gfx::ICanvas &canvas)
        -double m_width
        -double m_height
        -std::shared_ptr<GroupShape> m_shapes
        -RGBAColor m_background
    }

    class IShape {
        <<interface>>
        +GetFrame() : RectD
        +SetFrame(const RectD &rect)
        +GetOutlineStyle() : std::shared_ptr<ILineStyle>
        +GetFillStyle() : std::shared_ptr<IFillStyle>
    }

    class Shape {
        +Shape(const RectD &frame, std::shared_ptr<ILineStyle> outlineStyle, std::shared_ptr<IFillStyle> fillStyle)
        +GetFrame() : RectD
        +SetFrame(const RectD &rect)
        +GetOutlineStyle() : std::shared_ptr<ILineStyle>
        +GetFillStyle() : std::shared_ptr<IFillStyle>
        -RectD m_frame
        -std::shared_ptr<ILineStyle> m_outlineStyle
        -std::shared_ptr<IFillStyle> m_fillStyle
    }

    class IGroupShape {
        <<interface>>
        +GetShapesCount() : size_t
        +InsertShape(const std::shared_ptr<IShape> &shape, size_t position)
        +GetShapeAtIndex(size_t index) : std::shared_ptr<IShape>
        +RemoveShapeAtIndex(size_t index)
    }

    class GroupShape {
        +InsertShape(const std::shared_ptr<IShape> &shape, size_t position)
        +GetShapeAtIndex(size_t index) : std::shared_ptr<IShape>
        +RemoveShapeAtIndex(size_t index)
        +GetFrame() : RectD
        +SetFrame(const RectD &rect)
        +Draw(gfx::ICanvas &canvas)
        -std::vector<std::shared_ptr<IShape>> m_shapes
        -std::shared_ptr<GroupLineStyle> m_outlineStyle
        -std::shared_ptr<GroupFillStyle> m_fillStyle
    }

    class ILineStyle {
        <<interface>>
        +GetColor() : std::optional<RGBAColor>
        +SetColor(RGBAColor color)
        +GetWidth() : double
        +SetWidth(double width)
    }

    class SimpleLineStyle {
        +SimpleLineStyle(std::optional<RGBAColor> color, std::optional<double> width)
        +GetColor() : std::optional<RGBAColor>
        +SetColor(RGBAColor color)
        +GetWidth() : double
        +SetWidth(double width)
        -std::optional<RGBAColor> m_color
        -double m_width
    }

    class GroupLineStyle {
        +GroupLineStyle(std::unique_ptr<IStyleEnumerator<ILineStyle>> enumerator)
        +GetColor() : std::optional<RGBAColor>
        +SetColor(RGBAColor color)
        +GetWidth() : double
        +SetWidth(double width)
        -std::unique_ptr<IStyleEnumerator<ILineStyle>> m_enumerator
    }

    class IFillStyle {
        <<interface>>
        +GetColor() : std::optional<RGBAColor>
        +SetColor(RGBAColor color)
    }

    class SimpleFillStyle {
        +SimpleFillStyle(std::optional<RGBAColor> color)
        +GetColor() : std::optional<RGBAColor>
        +SetColor(RGBAColor color)
        -std::optional<RGBAColor> m_color
    }

    class GroupFillStyle {
        +GroupFillStyle(std::unique_ptr<IStyleEnumerator<IFillStyle>> enumerator)
        +GetColor() : std::optional<RGBAColor>
        +SetColor(RGBAColor color)
        -std::unique_ptr<IStyleEnumerator<IFillStyle>> m_enumerator
    }

    class LineStyleEnumerator {
        +LineStyleEnumerator(std::vector<std::shared_ptr<IShape>> &items)
        +EnumerateAll(std::function<void(std::shared_ptr<ILineStyle>)> callback)
    }

    class FillStyleEnumerator {
        +FillStyleEnumerator(std::vector<std::shared_ptr<IShape>> &items)
        +EnumerateAll(std::function<void(std::shared_ptr<IFillStyle>)> callback)
    }

    class RectD {
        +double left
        +double top
        +double width
        +double height
    }

    class IStyle {
        <<interface>>
        +IsEnabled() : std::optional<bool>
        +Enable(bool enable)
        +GetColor() : std::optional<RGBAColor>
        +SetColor(RGBAColor color)
        ~IStyle() = default
    }

    class Style {
        +IsEnabled() : std::optional<bool> override
        +Enable(bool enable) override
        ~Style() override = default
        -std::optional<bool> m_enabled
    }

    class IStyleEnumerator {
        <<interface>>
        +~IStyleEnumerator()
        +EnumerateAll(std::function<void(std::shared_ptr<T>)>)
    }

    class LineStyleEnumerator {
        +LineStyleEnumerator(T &items)
        +EnumerateAll(std::function<void(std::shared_ptr<ILineStyle>)> callback) override
        -T &m_items
    }

    class FillStyleEnumerator {
        +FillStyleEnumerator(T &items)
        +EnumerateAll(std::function<void(std::shared_ptr<IFillStyle>)> callback) override
        -T &m_items
    }
    class IDrawable {
        +Draw(gfx::ICanvas &canvas) const
        ~IDrawable() = default
    }
class ICanvas {
<<interface>>
+SetLineColor(uint32_t color)
+SetFillColor(uint32_t color)
+SetLineWidth(double width)
+DrawLine(double x1, double y1, double x2, double y2)
+BeginFill(uint32_t color)
+EndFill()
+DrawPolygon(const std::vector<std::pair<double, double>> &vertices)
+DrawEllipse(double cx, double cy, double rx, double ry)
~ICanvas() = default
}

    class SVGCanvas {
        +SVGCanvas(unsigned int width = 900, unsigned int height = 900)
        +DrawEllipse(double cx, double cy, double rx, double ry) override
        +SetLineColor(uint32_t color) override
        +SetFillColor(uint32_t color) override
        +SetLineWidth(double width) override
        +DrawLine(double x1, double y1, double x2, double y2) override
        +BeginFill(uint32_t color) override
        +EndFill() override
        +DrawPolygon(const std::vector<std::pair<double, double>> &vertices) override
        +SaveToFile(const std::string &filename)
        ~SVGCanvas() override = default
        -bool m_beginFill
        -gfx::Color m_currentLineColor
        -gfx::Color m_currentFillColor
        -std::vector<std::string> m_buff
        -double m_lineWidth
        -std::stringstream m_file
    }

    class Rectangle {
        +constexpr static const char* type = "rectangle"
        +Draw(gfx::ICanvas &canvas) const final
    }

    class Ellipse {
        +constexpr static const char* type = "ellipse"
        +Draw(gfx::ICanvas &canvas) const final
    }

    class Triangle {
        +constexpr static const char* type = "triangle"
        +Draw(gfx::ICanvas &canvas) const final
    }

    Client o-- SlideService
    ICanvas <.. Client : "Use"
    SlideService o-- IShapeFactory
    SlideService *-- ISlide
    ICanvas <|.. SVGCanvas
    IDrawable <|.. ISlide
    IDrawable <|.. IShape
    ISlide <|.. Slide
    Slide o-- GroupShape
    Slide <.. IShape
    IShapeFactory <|.. ShapeFactory
    IShape <|.. Shape
    IShape <|.. IGroupShape
    IGroupShape <|.. GroupShape
    GroupShape <|-- IShape
    LineStyleEnumerator <.. GroupShape : "Use"
    FillStyleEnumerator <.. GroupShape : "Use"
    IStyle <|.. Style
    Style <|.. IFillStyle
    Style <|.. ILineStyle
    ILineStyle <|.. SimpleLineStyle
    IFillStyle <|.. SimpleFillStyle
    ILineStyle <|.. GroupLineStyle
    IFillStyle <|.. GroupFillStyle
    IStyleEnumerator <|.. LineStyleEnumerator
    IStyleEnumerator <|.. FillStyleEnumerator
    IStyleEnumerator <|.. GroupLineStyle : "Use"
    IStyleEnumerator <|.. GroupFillStyle : "Use"
    IStyle o-- Shape
    RectD o-- Shape
    ILineStyle o-- Shape
    IFillStyle o-- Shape
    Shape <|.. Rectangle
    Shape <|.. Ellipse
    Shape <|.. Triangle