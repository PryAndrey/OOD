#include "ReplaceTextCommand.h"

void ReplaceTextCommand::DoExecute()
{
	if (!m_position.has_value() || m_position.value() > m_documentItems.size())
	{
		throw std::invalid_argument("Wrong position");
	}

	auto documentItem = m_documentItems.at(m_position.value());
	auto paragraph = documentItem.GetParagraph();
	if (paragraph != nullptr)
	{
		m_replacedText = paragraph->GetText();
		paragraph->SetText(m_newText);
	}
	else
	{
		throw std::invalid_argument("There is no paragraph in this position");
	}
}

void ReplaceTextCommand::DoUnexecute()
{
	if (!m_position.has_value() || m_position.value() > m_documentItems.size())
	{
		throw std::invalid_argument("Wrong position");
	}

	auto documentItem = m_documentItems.at(m_position.value());
	auto paragraph = documentItem.GetParagraph();

	if (paragraph != nullptr)
	{
		paragraph->SetText(m_replacedText);
	}
	else
	{
		throw std::invalid_argument("There is no paragraph in this position");
	}
}

std::string ReplaceTextCommand::GetParamsForGlue()
{
	return "ReplaceText " + (m_position.has_value() ? std::to_string(m_position.value()) : "end");
}

bool ReplaceTextCommand::IsGlueAble() const
{
	return true;
}