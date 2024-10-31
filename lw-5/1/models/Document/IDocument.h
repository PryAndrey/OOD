#pragma once

#include "Items/DocumentItem.h"
#include <optional>

class IDocument
{
public:
	[[maybe_unused]] [[nodiscard]] virtual std::shared_ptr<IParagraph> InsertParagraph(const std::string& text,
		std::optional<size_t> position)
		= 0;

	[[maybe_unused]] [[nodiscard]] virtual std::shared_ptr<IImage> InsertImage(const std::string& path, int width, int height,
		std::optional<size_t> position)
		= 0;

	virtual void ReplaceText(const std::string& newText, std::optional<size_t> position) = 0;

	virtual void ResizeImage(int width, int height, std::optional<size_t> position) = 0;

	[[nodiscard]] virtual size_t GetItemsCount() const = 0;

	[[nodiscard]] virtual ConstDocumentItem GetItem(size_t index) const = 0;
	[[nodiscard]] virtual DocumentItem GetItem(size_t index) = 0;

	virtual void DeleteItem(size_t index) = 0;

	[[nodiscard]] virtual std::string GetTitle() const = 0;

	virtual void SetTitle(const std::string& title) = 0;

	[[nodiscard]] virtual bool CanUndo() const = 0;

	virtual void Undo() = 0;

	[[nodiscard]] virtual bool CanRedo() const = 0;

	virtual void Redo() = 0;

	virtual void Save(const std::string& path) const = 0;

	virtual ~IDocument() = default;
};
