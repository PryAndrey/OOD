#pragma once

#include "../../Document/Items/DocumentItem.h"
#include "../CCommand/CCommand.h"
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

class InsertParagraphCommand : public CCommand
{
public:
	InsertParagraphCommand(std::vector<DocumentItem>& documentItems,
		std::string text,
		std::optional<size_t> position = std::nullopt)
		: m_documentItems(documentItems)
		, m_text(std::move(text))
		, m_position(std::move(position))
	{
	}
	std::string GetParamsForGlue() override;

protected:
	void DoExecute() override;
	void DoUnexecute() override;
	bool IsGlueAble() const override;

private:
	std::vector<DocumentItem>& m_documentItems;
	std::string m_text;
	std::optional<size_t> m_position;
};
