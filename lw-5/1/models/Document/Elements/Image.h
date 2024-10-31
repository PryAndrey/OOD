#pragma once

#include <utility>

#include "IImage.h"

class Image : public IImage
{
public:
	Image(std::string imagePath, int height, int width)
		: m_path(std::move(imagePath))
		, m_width(width)
		, m_height(height) {};

	[[nodiscard]] std::string GetPath() const override;

	[[nodiscard]] int GetWidth() const override;

	[[nodiscard]] int GetHeight() const override;

	void Resize(int width, int height) override;

private:
	std::string m_path;
	int m_height;
	int m_width;
};
