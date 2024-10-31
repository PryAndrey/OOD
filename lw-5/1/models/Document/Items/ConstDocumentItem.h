#pragma once

#include "../Elements/Image.h"
#include "../Elements/Paragraph.h"
#include <memory>
#include <string>

class ConstDocumentItem
{
public:

    ConstDocumentItem(const std::string& imagePath, int height, int width):
            m_image(std::make_shared<Image>(imagePath, height, width))
    {};

    explicit ConstDocumentItem(const std::string& text):
            m_paragraph(std::make_shared<Paragraph>(text))
    {};

	[[nodiscard]] std::shared_ptr<const IImage> GetImage() const;

	[[nodiscard]] std::shared_ptr<const IParagraph> GetParagraph()const;

	virtual ~ConstDocumentItem() = default;

private:
    std::shared_ptr<Image> m_image = nullptr;
    std::shared_ptr<Paragraph> m_paragraph = nullptr;
};
