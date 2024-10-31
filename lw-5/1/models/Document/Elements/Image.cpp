#include "Image.h"

void Image::Resize(int width, int height)
{
	m_width = width > 0 ? width : -width;
	m_height = height > 0 ? height : -height;
}

int Image::GetHeight() const
{
	return m_height;
}

int Image::GetWidth() const
{
	return m_width;
}

std::string Image::GetPath() const
{
	return m_path;
}
