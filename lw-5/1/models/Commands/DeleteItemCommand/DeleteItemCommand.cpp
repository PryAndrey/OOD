#include "DeleteItemCommand.h"

void DeleteItemCommand::DoExecute()
{
	if (m_documentItems.empty())
	{
		return;
	}

	if (m_position > m_documentItems.size())
	{
		throw std::invalid_argument("Wrong position");
	}

	m_deletedDocumentItem = std::make_unique<DocumentItem>(m_documentItems.at(m_position));

	m_documentItems.erase(m_documentItems.begin() + m_position);
}

void DeleteItemCommand::DoUnexecute()
{
	if (m_deletedDocumentItem == nullptr)
	{
		return;
	}

	m_documentItems.insert(
		m_documentItems.begin() + m_position,
		*m_deletedDocumentItem);

	m_deletedDocumentItem = nullptr;
}

std::string DeleteItemCommand::GetParamsForGlue()
{
	return "DeleteItem " + std::to_string(m_position);
}

bool DeleteItemCommand::IsGlueAble() const
{
	return false;
}
