#include "InsertParagraphCommand.h"

void InsertParagraphCommand::DoExecute()
{
    DocumentItem documentItem(m_text);

    if (!m_position.has_value())
    {
        m_documentItems.push_back(documentItem);
        return;
    }

    if (m_position.value() > m_documentItems.size())
    {
        throw std::invalid_argument("Wrong position");
    }

    m_documentItems.insert(m_documentItems.begin() + m_position.value(), documentItem);
}

void InsertParagraphCommand::DoUnexecute()
{
    if (m_documentItems.empty())
    {
        return;
    }

    if (!m_position.has_value())
    {
        m_documentItems.pop_back();
        return;
    }

    if (m_position.value() < m_documentItems.size())
    {
        m_documentItems.erase(m_documentItems.begin() + m_position.value());
    }
}


std::string InsertParagraphCommand::GetParamsForGlue()
{
	return "InsertParagraph " + (m_position.has_value() ? std::to_string(m_position.value()) : "end") + " " + m_text;
}

bool InsertParagraphCommand::IsGlueAble() const
{
	return false;
}