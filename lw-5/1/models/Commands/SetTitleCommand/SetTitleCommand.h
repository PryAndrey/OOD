#pragma once

#include "../CCommand/CCommand.h"
#include <iostream>
#include <utility>

class SetTitleCommand : public CCommand
{
public:
	SetTitleCommand(std::string& title, std::string newTitle)
		: m_title(title)
		, m_newTitle(std::move(newTitle))
	{
	}
	std::string GetParamsForGlue() override;

protected:
	void DoExecute() override;
	void DoUnexecute() override;
	bool IsGlueAble() const override;

private:
	std::string& m_title;
	std::string m_newTitle;
};
