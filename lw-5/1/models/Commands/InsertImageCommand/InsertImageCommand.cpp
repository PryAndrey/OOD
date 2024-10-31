#include "InsertImageCommand.h"

void InsertImageCommand::DoExecute()
{
    DocumentItem documentItem(m_imagePath, m_height, m_width);

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


void InsertImageCommand::DoUnexecute()
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

std::string InsertImageCommand::GetParamsForGlue()
{
	return "InsertImage " + (m_position.has_value() ? std::to_string(m_position.value()) : "end");
}

bool InsertImageCommand::IsGlueAble() const
{
	return false;
}