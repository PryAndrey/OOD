#include "ConstDocumentItem.h"

std::shared_ptr<const IImage> ConstDocumentItem::GetImage() const
{
    if (m_image == nullptr)
    {
        return nullptr;
    }
    return std::static_pointer_cast<const IImage>(m_image);
}

std::shared_ptr<const IParagraph> ConstDocumentItem::GetParagraph() const
{
    if (m_paragraph == nullptr)
    {
        return nullptr;
    }
    return std::static_pointer_cast<const IParagraph>(m_paragraph);
}