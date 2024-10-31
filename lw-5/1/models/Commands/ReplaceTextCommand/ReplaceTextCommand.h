#pragma once

#include "../../Document/Items/DocumentItem.h"
#include "../CCommand/CCommand.h"
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>

class ReplaceTextCommand : public CCommand
{
public:
	ReplaceTextCommand(std::vector<DocumentItem>& documentItems,
		std::string newText,
		std::optional<size_t> position)
		: m_documentItems(documentItems)
		, m_newText(std::move(newText))
		, m_position(std::move(position)) {};
	std::string GetParamsForGlue() override;

protected:
	void DoExecute() override;
	void DoUnexecute() override;
	bool IsGlueAble() const override;

private:
	std::vector<DocumentItem>& m_documentItems;
	std::string m_replacedText;
	std::string m_newText;
	std::optional<size_t> m_position;
};
