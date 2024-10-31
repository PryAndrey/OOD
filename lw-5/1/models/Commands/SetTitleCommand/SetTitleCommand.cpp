#include "SetTitleCommand.h"

void SetTitleCommand::DoExecute()
{
    std::swap(m_title, m_newTitle);
}

void SetTitleCommand::DoUnexecute()
{
    std::swap(m_newTitle, m_title);
}

std::string SetTitleCommand::GetParamsForGlue()
{
	return ("SetTitle end");
}

bool SetTitleCommand::IsGlueAble() const
{
	return true;
}