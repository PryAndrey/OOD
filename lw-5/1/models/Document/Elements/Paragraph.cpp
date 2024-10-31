#include "Paragraph.h"

std::string Paragraph::GetText() const
{
    return m_text;
}

void Paragraph::SetText(const std::string &text)
{
    m_text = text;
}

