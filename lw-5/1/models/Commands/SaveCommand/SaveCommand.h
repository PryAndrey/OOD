#pragma once

#include "../../Document/Items/DocumentItem.h"
#include "../CCommand/CCommand.h"
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

class SaveCommand : public CCommand
{
public:
	SaveCommand(const std::vector<DocumentItem>& documentItems, std::string path, std::string title)
		: m_documentItems(documentItems)
		, m_path(std::move(path))
		, m_title(std::move(title))
	{
	}
	std::string GetParamsForGlue() override;

protected:
	void DoExecute() override;
	void DoUnexecute() override;
	bool IsGlueAble() const override;

private:
	const std::vector<DocumentItem>& m_documentItems;
	std::string m_path;
	std::string m_title;

	static std::string htmlTextEncode(const std::string& text);
	static std::string htmlNameEncode(const std::string& text);
};
