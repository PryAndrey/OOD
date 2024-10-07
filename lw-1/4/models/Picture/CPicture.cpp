#include "CPicture.h"
#include <iostream>

using namespace std;

namespace shapes
{
void shapes::CPicture::AddShape(const std::string& id, std::unique_ptr<CShape> shape)
{
	if (m_shapes.find(id) != m_shapes.end())
	{
		throw invalid_argument("That ID already used");
	}
	m_shapes.emplace(id, std::move(shape));
}

void shapes::CPicture::MoveShape(const string& id, double dx, double dy)
{
	if (m_shapes.find(id) == m_shapes.end())
	{
		throw invalid_argument("Shape with that ID doesnt exist");
	}
	return m_shapes.at(id)->Move(dx, dy);
}

void shapes::CPicture::MovePicture(double dx, double dy)
{
	for (auto& shape : m_shapes)
	{
		shape.second->Move(dx, dy);
	}
}

void shapes::CPicture::DeleteShape(const string& id)
{
	auto it = m_shapes.find(id);
	if (it == m_shapes.end())
	{
		throw invalid_argument("Shape with that ID doesnt exist");
	}
	m_shapes.erase(it);
}

void shapes::CPicture::List() const
{
	int number = 1;
	for (const auto& shape : m_shapes)
	{
		std::cout << number++ << " "
			 << shape.second->GetType() << " "
			 << shape.second->GetId() << " "
			 << shape.second->GetColor() << " "
			 << shape.second->GetStringParams()
			 << std::endl;
	}
}

void shapes::CPicture::ChangeColor(const string& id, const string& color)
{
	if (m_shapes.find(id) == m_shapes.end())
	{
		throw invalid_argument("Shape with that ID doesnt exist");
	}

	return m_shapes.at(id)->SetColor(color);
}

void shapes::CPicture::ChangeShape(const string& id, std::unique_ptr<IShapeType> newShapeType)
{
	if (m_shapes.find(id) == m_shapes.end())
	{
		throw invalid_argument("Shape with that ID doesnt exist");
	}

	m_shapes.at(id)->SetNewShapeType(std::move(newShapeType));
}

void shapes::CPicture::DrawShape(const string& id, gfx::ICanvas& canvas) const
{
	if (m_shapes.find(id) == m_shapes.end())
	{
		throw invalid_argument("Shape with that ID doesnt exist");
	}
	m_shapes.at(id)->Draw(canvas);
}

void shapes::CPicture::DrawPicture(gfx::ICanvas& canvas) const
{
	for (const auto& shape : m_shapes)
	{
		shape.second->Draw(canvas);
	}
}

std::string CPicture::GetShapeById(const string& id) const
{
	if (m_shapes.find(id) == m_shapes.end())
	{
		throw invalid_argument("Shape with that ID doesnt exist");
	}
	string shapeText = m_shapes.at(id)->GetType() + " "
		+ m_shapes.at(id)->GetId() + " "
		+ m_shapes.at(id)->GetColor() + " "
		+ m_shapes.at(id)->GetStringParams();

	return shapeText;
}
} // namespace shapes
