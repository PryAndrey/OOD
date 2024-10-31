#pragma once

#include "models/document/Document.h"
#include "models/menu/Menu.h"
#include <sstream>
#include <utility>

class CommandHandler
{
public:
	CommandHandler(std::shared_ptr<IMenu> menu, std::unique_ptr<IDocument> document)
		: m_menu(std::move(menu))
		, m_document(std::move(document))
	{
		m_menu->AddItem("Help", "Help", [this](std::istream&) { m_menu->ShowInstructions(); });
		AddMenuItem("InsertParagraph", "Insert paragraph", &CommandHandler::InsertParagraph);
		AddMenuItem("InsertImage", "Insert image", &CommandHandler::InsertImage);
		AddMenuItem("List", "Show document", &CommandHandler::List);
		AddMenuItem("SetTitle", "Set title", &CommandHandler::SetTitle);
		AddMenuItem("ReplaceText", "Replace text", &CommandHandler::ReplaceText);
		AddMenuItem("ResizeImage", "Resize Image", &CommandHandler::ResizeImage);
		AddMenuItem("DeleteItem", "Delete item", &CommandHandler::DeleteItem);
		AddMenuItem("Undo", "Undo command", &CommandHandler::Undo);
		AddMenuItem("Redo", "Redo undone command", &CommandHandler::Redo);
		AddMenuItem("Save", "Save to html", &CommandHandler::Save);
	}

private:
	std::shared_ptr<IMenu> m_menu;
	std::unique_ptr<IDocument> m_document;

	typedef void (CommandHandler::* MenuHandler)(std::istream& iss);

	void AddMenuItem(const std::string& commandName, const std::string& description, MenuHandler handler)
	{
		m_menu->AddItem(commandName, description, [this, handler](std::istream& iss) {
			(this->*handler)(iss);
		});
	}

	void List(std::istream&)
	{
		std::cout << "Title: " << m_document->GetTitle() << "\n";

		for (int i = 0; i < m_document->GetItemsCount(); i++)
		{
			auto documentItem = m_document->GetItem(i);
			auto paragraph = documentItem.GetParagraph();
			if (paragraph != nullptr)
			{
				std::cout << i << ". Paragraph: " << paragraph->GetText() << "\n";
			}

			auto image = documentItem.GetImage();
			if (image != nullptr)
			{
				std::cout << i << ". Image: " << image->GetWidth() << " " << image->GetHeight() << " " << image->GetPath() << "\n";
			}
		}
	}

	void InsertParagraph(std::istream& iss)
	{
		std::string positionStr, text;

		iss >> positionStr;

		std::stringstream issTemp;
		issTemp << iss.rdbuf();
		text = issTemp.str();

		std::optional<size_t> position;
		if (positionStr == "end")
		{
			position = std::nullopt;
		}
		else
		{
			try
			{
				position = std::stoi(positionStr);
			}
			catch (...)
			{
				throw std::invalid_argument("Invalid position format");
			}
		}

		m_document->InsertParagraph(text, position);
	}

	void InsertImage(std::istream& iss)
	{
		std::string positionStr, width, height, path;

		iss >> positionStr >> width >> height >> path;

		std::optional<size_t> position;
		int widthNum, heightNum;

		if (positionStr == "end")
		{
			position = std::nullopt;
		}
		else
		{
			try
			{
				position = std::stoi(positionStr);
			}
			catch (...)
			{
				throw std::invalid_argument("Invalid position format");
			}
		}
		try
		{
			widthNum = std::stoi(width);
			heightNum = std::stoi(height);
		}
		catch (...)
		{
			throw std::invalid_argument("Invalid params format");
		}
		m_document->InsertImage(path, widthNum, heightNum, position);
	}

	void ResizeImage(std::istream& iss)
	{
		std::string newWidth, newHeight;
		std::string positionStr;

		iss >> positionStr >> newWidth >> newHeight;
		int width, height;
		std::optional<size_t> position;
		try
		{
			position = std::stoi(positionStr);
			width = std::stoi(newWidth);
			height = std::stoi(newHeight);
		}
		catch (...)
		{
			throw std::invalid_argument("Invalid params format");
		}

		m_document->ResizeImage(width, height, position);
	}

	void SetTitle(std::istream& iss)
	{
		std::string title;

		std::stringstream issTemp;
		issTemp << iss.rdbuf();
		title = issTemp.str();

		m_document->SetTitle(title);
	}

	void ReplaceText(std::istream& iss)
	{
		std::string newText;
		std::string positionStr;

		iss >> positionStr;

		std::stringstream issTemp;
		issTemp << iss.rdbuf();
		newText = issTemp.str();

		std::optional<size_t> position;
		try
		{
			position = std::stoi(positionStr);
		}
		catch (...)
		{
			throw std::invalid_argument("Invalid position format");
		}

		m_document->ReplaceText(newText, position);
	}

	void DeleteItem(std::istream& iss)
	{
		std::string positionStr;

		iss >> positionStr;

		size_t position;
		try
		{
			position = std::stoi(positionStr);
		}
		catch (...)
		{
			throw std::invalid_argument("Invalid position format");
		}

		m_document->DeleteItem(position);
	}

	void Undo(std::istream&)
	{
		if (m_document->CanUndo())
		{
			m_document->Undo();
		}
		else
		{
			std::cout << "Can't undo" << std::endl;
		}
	}

	void Redo(std::istream&)
	{
		if (m_document->CanRedo())
		{
			m_document->Redo();
		}
		else
		{
			std::cout << "Can't redo" << std::endl;
		}
	}

	void Save(std::istream& iss)
	{
		std::string path;

		iss >> path;

		m_document->Save(path);
	}
};