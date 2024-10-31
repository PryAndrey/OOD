#pragma once

#include "../../Document/Items/DocumentItem.h"
#include "../CCommand/CCommand.h"
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

class InsertImageCommand : public CCommand
{
public:
	InsertImageCommand(std::vector<DocumentItem>& documentItems, std::string imagePath,
		int width, int height, std::optional<size_t> position = std::nullopt)
		: m_documentItems(documentItems)
		, m_imagePath(std::move(imagePath))
		, m_width(width)
		, m_height(height)
		, m_position(position)
	{
	}
	std::string GetParamsForGlue() override;

protected:
	void DoExecute() override;
	void DoUnexecute() override;
	bool IsGlueAble() const override;

private:
	std::vector<DocumentItem>& m_documentItems;
	std::string m_imagePath;
	int m_width;
	int m_height;
	std::optional<size_t> m_position;
};
