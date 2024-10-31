#pragma once

#include "ConstDocumentItem.h"
#include <memory>

class DocumentItem : public ConstDocumentItem
{
public:
	DocumentItem(const std::string& imagePath, int height, int width)
		: ConstDocumentItem(imagePath, height, width) {};

	explicit DocumentItem(const std::string& text)
		: ConstDocumentItem(text) {};

	std::shared_ptr<IImage> GetImage();

	std::shared_ptr<IParagraph> GetParagraph();
};
