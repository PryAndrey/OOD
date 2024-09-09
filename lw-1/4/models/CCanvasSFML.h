#pragma once

#include "Interface/ICanvas.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
using namespace sf;

class CCanvasSFML : public ICanvas
{
public:
	explicit CCanvasSFML(unsigned int width = 900, unsigned int height = 900)
		: m_width(width)
		, m_height(height)
	{
		m_window = new RenderWindow(VideoMode(width, height), "Canvas");
	}
//other file
	void DrawLine(CPoint from, CPoint to, CColor lineColor) override
	{
		sf::VertexArray line(sf::Lines, 2);

		line[0].position = sf::Vector2f((float)from.x, (float)from.y);
		line[0].color = Color(lineColor.GetColor());

		line[1].position = sf::Vector2f((float)to.x, (float)to.y);
		line[1].color = Color(lineColor.GetColor());

		m_window->draw(line);
	}

	void DrawPolygon(std::vector<CPoint> points, CColor outlineColor, CColor fillColor) override
	{
		sf::ConvexShape triangle;
		triangle.setPointCount(3);
		triangle.setPoint(0, sf::Vector2f((float)points[0].x, (float)points[0].y));
		triangle.setPoint(1, sf::Vector2f((float)points[1].x, (float)points[1].y));
		triangle.setPoint(2, sf::Vector2f((float)points[2].x, (float)points[2].y));

		triangle.setOutlineThickness(2);

		triangle.setOutlineColor(Color(outlineColor.GetColor()));
		triangle.setFillColor(Color(fillColor.GetColor()));

		m_window->draw(triangle);
	}

	void DrawRectangle(CPoint topLeftPoint, double width, double height, CColor outlineColor, CColor fillColor) override
	{
		RectangleShape rectangle(Vector2f((float)width, (float)height));
		rectangle.setPosition(Vector2f((float)topLeftPoint.x, (float)topLeftPoint.y));

		rectangle.setOutlineThickness(2);

		rectangle.setOutlineColor(Color(outlineColor.GetColor()));
		rectangle.setFillColor(Color(fillColor.GetColor()));

		m_window->draw(rectangle);
	}

	void DrawCircle(CPoint center, double radius, CColor outlineColor, CColor fillColor) override
	{
		CircleShape circle((float)radius);
		circle.setPosition(Vector2f((float)center.x, (float)center.y));

		circle.setOutlineThickness(2);

		circle.setOutlineColor(Color(outlineColor.GetColor()));
		circle.setFillColor(Color(fillColor.GetColor()));

		m_window->draw(circle);
	}

	void Display() override
	{
		m_window->display();
		while (m_window->isOpen())
		{
			Event event{};
			while (m_window->pollEvent(event))
			{
				if (event.type == Event::Closed)
					m_window->close();
			}
		}
	}

	RenderWindow* m_window;
	unsigned int m_width;
	unsigned int m_height;
};
