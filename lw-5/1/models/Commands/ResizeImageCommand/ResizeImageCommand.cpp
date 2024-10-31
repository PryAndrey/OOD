#include "ResizeImageCommand.h"

void ResizeImageCommand::DoExecute()
{
	if (!m_position.has_value() || m_position.value() > m_documentItems.size())
	{
		throw std::invalid_argument("Wrong position");
	}

	auto image = m_documentItems.at(m_position.value()).GetImage();
	if (image != nullptr)
	{
		m_replacedHeight = image->GetHeight();
		m_replacedWidth = image->GetWidth();
		image->Resize(m_newWidth, m_newHeight);
	}
	else
	{
		throw std::invalid_argument("There is no image in this position");
	}
}

void ResizeImageCommand::DoUnexecute()
{
	if (!m_position.has_value() || m_position.value() > m_documentItems.size())
	{
		throw std::invalid_argument("Wrong position");
	}

	auto image = m_documentItems.at(m_position.value()).GetImage();

	if (image != nullptr)
	{
		image->Resize(m_replacedWidth, m_replacedHeight);
	}
	else
	{
		throw std::invalid_argument("There is no image in this position");
	}
}

std::string ResizeImageCommand::GetParamsForGlue()
{
	return "ResizeImage " + (m_position.has_value() ? std::to_string(m_position.value()) : "end");
}

bool ResizeImageCommand::IsGlueAble() const
{
	return true;
}