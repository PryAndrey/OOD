#pragma once

#include "../../Document/Items/DocumentItem.h"
#include "../CCommand/CCommand.h"
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>

class ResizeImageCommand : public CCommand
{
public:
	ResizeImageCommand(std::vector<DocumentItem>& documentItems,
		int newWidth, int newHeight,
		std::optional<size_t> position)
		: m_documentItems(documentItems)
		, m_newWidth(newWidth)
		, m_newHeight(newHeight)
		, m_position(position) {};
	std::string GetParamsForGlue() override;

protected:
	void DoExecute() override;
	void DoUnexecute() override;
	bool IsGlueAble() const override;

private:
	std::vector<DocumentItem>& m_documentItems;
	int m_replacedHeight = 0;
	int m_replacedWidth = 0;
	int m_newHeight;
	int m_newWidth;
	std::optional<size_t> m_position;
};
