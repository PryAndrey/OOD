#pragma once

#include "../../Document/Items/DocumentItem.h"
#include "../CCommand/CCommand.h"
#include <iostream>
#include <optional>
#include <vector>

class DeleteItemCommand : public CCommand
{
public:
    DeleteItemCommand(std::vector<DocumentItem>& documentItems, size_t position)
            : m_documentItems(documentItems), m_position(position)
    {
	}
	std::string GetParamsForGlue() override;

protected:
    void DoExecute() override;
    void DoUnexecute() override;
	bool IsGlueAble() const override;
private:
    std::vector<DocumentItem>& m_documentItems;
    size_t m_position;
    std::unique_ptr<DocumentItem> m_deletedDocumentItem = nullptr;
};
