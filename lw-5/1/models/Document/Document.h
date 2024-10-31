#pragma once

#include "../commands/DeleteItemCommand/DeleteItemCommand.h"
#include "../commands/InsertImageCommand/InsertImageCommand.h"
#include "../commands/InsertParagraphCommand/InsertParagraphCommand.h"
#include "../commands/ReplaceTextCommand/ReplaceTextCommand.h"
#include "../commands/ResizeImageCommand/ResizeImageCommand.h"
#include "../commands/SaveCommand/SaveCommand.h"
#include "../commands/SetTitleCommand/SetTitleCommand.h"
#include "History/History.h"
#include "IDocument.h"
#include "Items/DocumentItem.h"
#include <vector>

class Document : public IDocument
{
public:
	std::shared_ptr<IParagraph> InsertParagraph(const std::string& text,
		std::optional<size_t> position = std::nullopt) override;

	void ReplaceText(const std::string& newText, std::optional<size_t> position) override;

	std::shared_ptr<IImage> InsertImage(const std::string& path, int width, int height,
		std::optional<size_t> position = std::nullopt) override;

	void ResizeImage(int width, int height, std::optional<size_t> position) override;

	[[nodiscard]] size_t GetItemsCount() const override;

	[[nodiscard]] ConstDocumentItem GetItem(size_t index) const override;

	DocumentItem GetItem(size_t index) override;

	void DeleteItem(size_t index) override;

	[[nodiscard]] std::string GetTitle() const override;

	void SetTitle(const std::string& title) override;

	[[nodiscard]] bool CanUndo() const override;

	void Undo() override;

	[[nodiscard]] bool CanRedo() const override;

	void Redo() override;

	void Save(const std::string& path) const override;

private:
	std::string m_title;
	History m_history;
	std::vector<DocumentItem> m_documentItems;
};
//Перенести создание в image/paragraph