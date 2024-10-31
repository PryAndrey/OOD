#include "DocumentItem.h"

std::shared_ptr<IImage> DocumentItem::GetImage()
{
    return std::const_pointer_cast<IImage>(ConstDocumentItem::GetImage());
}

std::shared_ptr<IParagraph> DocumentItem::GetParagraph()
{
    return std::const_pointer_cast<IParagraph>(ConstDocumentItem::GetParagraph());
}
