#include "../CommandHandler.h"
#include "../models/Commands/InsertImageCommand/InsertImageCommand.h"
#include "../models/Commands/ResizeImageCommand/ResizeImageCommand.h"
#include "../models/Document/History/History.h"
#include "../models/Document/IDocument.h"
#include "../models/Menu/Menu.h"
#include "../models/commands/DeleteItemCommand/DeleteItemCommand.h"
#include "../models/commands/InsertParagraphCommand/InsertParagraphCommand.h"
#include "../models/commands/ReplaceTextCommand/ReplaceTextCommand.h"
#include "../models/commands/SaveCommand/SaveCommand.h"
#include "../models/commands/SetTitleCommand/SetTitleCommand.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class InsertParagraphCommandTestable : public InsertParagraphCommand
{
public:
	InsertParagraphCommandTestable(std::vector<DocumentItem>& documentItems,
		std::string text,
		std::optional<size_t> position)
		: InsertParagraphCommand(documentItems, std::move(text), position)
	{
	}

	void TestDoExecute()
	{
		DoExecute();
	}

	void TestDoUnexecute()
	{
		DoUnexecute();
	}
};

class InsertImageCommandTestable : public InsertImageCommand
{
public:
	InsertImageCommandTestable(std::vector<DocumentItem>& documentItems,
		std::string imagePath,
		int width,
		int height,
		std::optional<size_t> position)
		: InsertImageCommand(documentItems, std::move(imagePath), width, height, position)
	{
	}

	void TestDoExecute()
	{
		DoExecute();
	}

	void TestDoUnexecute()
	{
		DoUnexecute();
	}
};

class ReplaceTextCommandTestable : public ReplaceTextCommand
{
public:
	ReplaceTextCommandTestable(std::vector<DocumentItem>& documentItems,
		std::string newText,
		std::optional<size_t> position)
		: ReplaceTextCommand(documentItems, std::move(newText), position)
	{
	}

	void TestDoExecute()
	{
		DoExecute();
	}

	void TestDoUnexecute()
	{
		DoUnexecute();
	}
};

class ResizeImageCommandTestable : public ResizeImageCommand
{
public:
	ResizeImageCommandTestable(
		std::vector<DocumentItem>& documentItems,
		int width,
		int height,
		std::optional<size_t> position)
		: ResizeImageCommand(documentItems, width, height, position)
	{
	}

	void TestDoExecute()
	{
		DoExecute();
	}

	void TestDoUnexecute()
	{
		DoUnexecute();
	}
};

class DeleteItemCommandTestable : public DeleteItemCommand
{
public:
	DeleteItemCommandTestable(std::vector<DocumentItem>& documentItems, size_t position)
		: DeleteItemCommand(documentItems, position)
	{
	}

	// Public methods for calling protected methods
	void TestDoExecute()
	{
		DoExecute();
	}

	void TestDoUnexecute()
	{
		DoUnexecute();
	}
};

class SetTitleCommandTestable : public SetTitleCommand
{
public:
	SetTitleCommandTestable(std::string& title, std::string newTitle)
		: SetTitleCommand(title, std::move(newTitle))
	{
	}

	// Public methods to call the protected methods
	void TestDoExecute()
	{
		DoExecute();
	}

	void TestDoUnexecute()
	{
		DoUnexecute();
	}
};

class SaveCommandTestable : public SaveCommand
{
public:
	SaveCommandTestable(const std::vector<DocumentItem>& documentItems, std::string path, std::string title)
		: SaveCommand(documentItems, std::move(path), std::move(title))
	{
	}

	void TestDoExecute()
	{
		DoExecute();
	}

	void TestDoUnexecute()
	{
		DoUnexecute();
	}
};

TEST(InsertParagraphCommandTest, InsertAtEnd)
{
	std::vector<DocumentItem> documentItems;
	std::string text = "New paragraph text";

	InsertParagraphCommandTestable command(documentItems, text, std::nullopt);

	command.TestDoExecute();

	ASSERT_EQ(documentItems.size(), 1);

	auto paragraph = std::dynamic_pointer_cast<Paragraph>(documentItems[0].GetParagraph());
	ASSERT_NE(paragraph, nullptr);
	EXPECT_EQ(paragraph->GetText(), text);

	command.TestDoUnexecute();

	EXPECT_TRUE(documentItems.empty());
}

TEST(InsertParagraphCommandTest, InsertAtPosition)
{
	std::string text = "Existing paragraph";
	DocumentItem documentItem(text);
	std::vector<DocumentItem> documentItems = { documentItem };

	std::string textInserted = "Inserted paragraph";
	size_t position = 0;

	InsertParagraphCommandTestable command(documentItems, textInserted, position);

	command.TestDoExecute();

	ASSERT_EQ(documentItems.size(), 2);

	auto paragraph1 = std::dynamic_pointer_cast<Paragraph>(documentItems[position].GetParagraph());
	ASSERT_NE(paragraph1, nullptr);
	EXPECT_EQ(paragraph1->GetText(), textInserted);

	command.TestDoUnexecute();

	ASSERT_EQ(documentItems.size(), 1);
	EXPECT_EQ(documentItems[0].GetParagraph()->GetText(), "Existing paragraph");
}

TEST(InsertParagraphCommandTest, InsertAtInvalidPositionError)
{
	std::vector<DocumentItem> documentItems;
	std::string text = "Text for invalid position";
	size_t invalidPosition = 10;

	InsertParagraphCommandTestable command(documentItems, text, invalidPosition);

	EXPECT_THROW(command.TestDoExecute(), std::invalid_argument);
	EXPECT_TRUE(documentItems.empty());
}

TEST(ReplaceTextCommandTest, DoExecuteReplaceTextAtPosition)
{
	std::vector<DocumentItem> documentItems;
	std::string oldText = "Original text";
	documentItems.emplace_back(oldText);

	std::string newText = "Replaced text";
	size_t position = 0;

	ReplaceTextCommandTestable command(documentItems, newText, position);

	command.TestDoExecute();

	auto paragraph = std::dynamic_pointer_cast<Paragraph>(documentItems[position].GetParagraph());
	ASSERT_NE(paragraph, nullptr);
	EXPECT_EQ(paragraph->GetText(), newText);

	command.TestDoUnexecute();

	EXPECT_EQ(paragraph->GetText(), "Original text");
}

TEST(ReplaceTextCommandTest, DoExecuteReplaceTextWithInvalidPositionError)
{
	std::vector<DocumentItem> documentItems;
	std::string newText = "Text for invalid position";
	size_t invalidPosition = 10;

	ReplaceTextCommandTestable command(documentItems, newText, invalidPosition);

	EXPECT_THROW(command.TestDoExecute(), std::invalid_argument);
}

TEST(ReplaceTextCommandTest, DoExecuteReplaceTextWithoutPositionError)
{
	std::vector<DocumentItem> documentItems;
	std::string newText = "Text for no position";

	ReplaceTextCommandTestable command(documentItems, newText, std::nullopt);

	EXPECT_THROW(command.TestDoExecute(), std::invalid_argument);
}

TEST(ReplaceTextCommandTest, DoUnexecuteRestoreOriginalText)
{
	std::vector<DocumentItem> documentItems;
	std::string oldText = "Initial text";
	documentItems.emplace_back(oldText);

	std::string newText = "New text";
	size_t position = 0;

	ReplaceTextCommandTestable command(documentItems, newText, position);

	command.TestDoExecute();

	auto paragraph = std::dynamic_pointer_cast<Paragraph>(documentItems[position].GetParagraph());
	ASSERT_NE(paragraph, nullptr);
	EXPECT_EQ(paragraph->GetText(), newText);

	command.TestDoUnexecute();

	EXPECT_EQ(paragraph->GetText(), "Initial text");
}

TEST(DeleteItemCommandTest, DoExecuteDeleteItemAtSpecifiedPosition)
{
	std::vector<DocumentItem> documentItems;
	std::string text1 = "Paragraph 1";
	std::string text2 = "Paragraph 2";
	documentItems.emplace_back(text1);
	documentItems.emplace_back(text2);

	size_t position = 1;
	DeleteItemCommandTestable command(documentItems, position);

	command.TestDoExecute();

	ASSERT_EQ(documentItems.size(), 1);
	EXPECT_EQ(documentItems[0].GetParagraph()->GetText(), "Paragraph 1");

	command.TestDoUnexecute();

	ASSERT_EQ(documentItems.size(), 2);
	EXPECT_EQ(documentItems[1].GetParagraph()->GetText(), "Paragraph 2");
}

TEST(DeleteItemCommandTest, DoExecuteDeleteItemWithInvalidPositionError)
{
	std::vector<DocumentItem> documentItems;
	std::string text = "Paragraph 1";
	documentItems.emplace_back(text);

	size_t invalidPosition = 5;
	DeleteItemCommandTestable command(documentItems, invalidPosition);

	EXPECT_THROW(command.TestDoExecute(), std::invalid_argument);
}

TEST(DeleteItemCommandTest, DoExecuteDeleteOnlyItem)
{
	std::vector<DocumentItem> documentItems;
	std::string text = "Only paragraph";
	documentItems.emplace_back(text);

	size_t position = 0;
	DeleteItemCommandTestable command(documentItems, position);

	command.TestDoExecute();

	EXPECT_TRUE(documentItems.empty());

	command.TestDoUnexecute();

	ASSERT_EQ(documentItems.size(), 1);
	EXPECT_EQ(documentItems[0].GetParagraph()->GetText(), "Only paragraph");
}

TEST(DeleteItemCommandTest, DoExecuteDeleteItemAtPositionZero)
{
	std::vector<DocumentItem> documentItems;
	std::string text1 = "Paragraph 1";
	std::string text2 = "Paragraph 2";
	std::string text3 = "Paragraph 3";
	documentItems.emplace_back(text1);
	documentItems.emplace_back(text2);
	documentItems.emplace_back(text3);

	size_t position = 0;
	DeleteItemCommandTestable command(documentItems, position);

	command.TestDoExecute();

	ASSERT_EQ(documentItems.size(), 2);
	EXPECT_EQ(documentItems[0].GetParagraph()->GetText(), "Paragraph 2");

	command.TestDoUnexecute();

	ASSERT_EQ(documentItems.size(), 3);
	EXPECT_EQ(documentItems[0].GetParagraph()->GetText(), "Paragraph 1");
}

TEST(DeleteItemCommandTest, DoUnexecuteOnEmptyListError)
{
	std::vector<DocumentItem> documentItems;

	size_t position = 0;
	DeleteItemCommandTestable command(documentItems, position);

	EXPECT_NO_THROW(command.TestDoUnexecute());

	EXPECT_TRUE(documentItems.empty());
}

TEST(SetTitleCommandTest, DoExecuteSetsNewTitle)
{
	std::string title = "Original Title";
	std::string newTitle = "New Title";

	SetTitleCommandTestable command(title, newTitle);

	command.TestDoExecute();

	EXPECT_EQ(title, "New Title");

	command.TestDoUnexecute();

	EXPECT_EQ(title, "Original Title");
}

TEST(SetTitleCommandTest, DoUnexecuteRevertsToOldTitle)
{
	std::string title = "Initial Title";
	std::string newTitle = "Updated Title";

	SetTitleCommandTestable command(title, newTitle);

	command.TestDoExecute();

	EXPECT_EQ(title, "Updated Title");

	command.TestDoUnexecute();

	EXPECT_EQ(title, "Initial Title");
}

TEST(SetTitleCommandTest, RepeatedExecuteAndUnexecute)
{
	std::string title = "Start Title";
	std::string newTitle = "Changed Title";

	SetTitleCommandTestable command(title, newTitle);

	command.TestDoExecute();
	EXPECT_EQ(title, "Changed Title");

	command.TestDoUnexecute();
	EXPECT_EQ(title, "Start Title");

	command.TestDoExecute();
	EXPECT_EQ(title, "Changed Title");

	command.TestDoUnexecute();
	EXPECT_EQ(title, "Start Title");
}

TEST(SetTitleCommandTest, DoExecuteWithSameTitle)
{
	std::string title = "Same Title";

	SetTitleCommandTestable command(title, title);

	command.TestDoExecute();

	EXPECT_EQ(title, "Same Title");

	command.TestDoUnexecute();

	EXPECT_EQ(title, "Same Title");
}

TEST(SaveCommandTest, DoExecuteCreatesHtmlFile)
{
	std::vector<DocumentItem> documentItems;
	std::string title = "Test Document";
	std::string filePath = "test_output.html";

	documentItems.emplace_back("Paragraph 1");
	documentItems.emplace_back("Paragraph 2");

	SaveCommandTestable command(documentItems, filePath, title);

	command.TestDoExecute();

	std::ifstream inFile(filePath);
	ASSERT_TRUE(inFile.is_open());

	std::string line;
	std::getline(inFile, line);
	EXPECT_EQ(line, "<!DOCTYPE html>");

	std::getline(inFile, line);
	EXPECT_EQ(line, "<html>");

	std::getline(inFile, line);
	EXPECT_EQ(line, "<head>");

	std::getline(inFile, line);
	EXPECT_EQ(line, "<title>Test Document</title>");

	std::getline(inFile, line);
	EXPECT_EQ(line, "</head>");

	std::getline(inFile, line);
	EXPECT_EQ(line, "<body>");

	std::getline(inFile, line);
	EXPECT_EQ(line, "<p>Paragraph 1</p>");

	std::getline(inFile, line);
	EXPECT_EQ(line, "<p>Paragraph 2</p>");

	std::getline(inFile, line);
	EXPECT_EQ(line, "</body>");

	std::getline(inFile, line);
	EXPECT_EQ(line, "</html>");

	inFile.close();

	std::filesystem::remove(filePath);
}

TEST(SaveCommandTest, DoExecuteThrowsExceptionWhenFileCannotBeOpenedError)
{
	std::string invalidPath = "/invalid_path/test_output.html";
	std::vector<DocumentItem> documentItems;

	SaveCommandTestable command(documentItems, invalidPath, "Test Document");

	EXPECT_THROW(command.TestDoExecute(), std::runtime_error);
}

TEST(InsertImageCommandTest, InsertAtEnd)
{
	std::vector<DocumentItem> documentItems;
	std::string path = "../../1/example.jpg";

	InsertImageCommandTestable command(documentItems, path, 800, 900, std::nullopt);

	command.TestDoExecute();

	ASSERT_EQ(documentItems.size(), 1);

	auto image = std::dynamic_pointer_cast<Image>(documentItems[0].GetImage());
	ASSERT_NE(image, nullptr);
	EXPECT_EQ(image->GetPath(), path);
	EXPECT_EQ(image->GetWidth(), 800);
	EXPECT_EQ(image->GetHeight(), 900);

	command.TestDoUnexecute();

	EXPECT_TRUE(documentItems.empty());
}

TEST(InsertImageCommandTest, InsertAtPosition)
{
	std::string text = "Existing paragraph";
	DocumentItem documentItem(text);
	std::vector<DocumentItem> documentItems = { documentItem };

	std::string pathInserted = "../../1/example.jpg";
	size_t position = 0;

	InsertImageCommandTestable command(documentItems, pathInserted, 800, 900, position);

	command.TestDoExecute();

	ASSERT_EQ(documentItems.size(), 2);

	auto image = std::dynamic_pointer_cast<Image>(documentItems[position].GetImage());
	ASSERT_NE(image, nullptr);
	EXPECT_EQ(image->GetPath(), pathInserted);
	EXPECT_EQ(image->GetWidth(), 800);
	EXPECT_EQ(image->GetHeight(), 900);

	command.TestDoUnexecute();

	ASSERT_EQ(documentItems.size(), 1);
	EXPECT_EQ(documentItems[0].GetParagraph()->GetText(), "Existing paragraph");
}

TEST(InsertImageCommandTest, InsertAtInvalidPositionError)
{
	std::vector<DocumentItem> documentItems;
	std::string path = "../../1/example.jpg";
	size_t invalidPosition = 10;

	InsertImageCommandTestable command(documentItems, path, 800, 900, invalidPosition);

	EXPECT_THROW(command.TestDoExecute(), std::invalid_argument);
	EXPECT_TRUE(documentItems.empty());
}

TEST(ResizeImageCommandTest, DoExecuteResizeImageAtPosition)
{
	std::vector<DocumentItem> documentItems;
	std::string path = "../../1/example.jpg";
	size_t position = 0;

	InsertImageCommandTestable commandInsert(documentItems, path, 800, 900, position);

	commandInsert.TestDoExecute();

	ASSERT_EQ(documentItems.size(), 1);

	ResizeImageCommandTestable command(documentItems, 10, 10, position);

	command.TestDoExecute();

	auto image = std::dynamic_pointer_cast<Image>(documentItems[position].GetImage());
	ASSERT_NE(image, nullptr);
	EXPECT_EQ(image->GetPath(), path);
	EXPECT_EQ(image->GetWidth(), 10);
	EXPECT_EQ(image->GetHeight(), 10);

	command.TestDoUnexecute();

	EXPECT_EQ(image->GetWidth(), 800);
	EXPECT_EQ(image->GetHeight(), 900);
}

TEST(ResizeImageCommandTest, DoExecuteResizeImageWithInvalidPositionError)
{
	std::vector<DocumentItem> documentItems;
	std::string path = "../../1/example.jpg";
	size_t invalidPosition = 10;

	InsertImageCommandTestable commandInsert(documentItems, path, 800, 900, std::nullopt);

	commandInsert.TestDoExecute();

	ResizeImageCommandTestable command(documentItems, 10, 10, invalidPosition);

	EXPECT_THROW(command.TestDoExecute(), std::invalid_argument);
}

TEST(ResizeImageCommandTest, DoExecuteResizeImageWithoutPositionError)
{
	std::vector<DocumentItem> documentItems;

	ResizeImageCommandTestable command(documentItems, 10, 10, std::nullopt);

	EXPECT_THROW(command.TestDoExecute(), std::invalid_argument);
}

TEST(ResizeImageCommandTest, DoUnexecuteRestoreOriginalText)
{

	std::vector<DocumentItem> documentItems;
	std::string path = "../../1/example.jpg";
	size_t position = 0;

	InsertImageCommandTestable commandInsert(documentItems, path, 800, 900, std::nullopt);

	commandInsert.TestDoExecute();

	ResizeImageCommandTestable command(documentItems, 10, 10, position);

	command.TestDoExecute();

	auto image = std::dynamic_pointer_cast<Image>(documentItems[position].GetImage());
	ASSERT_NE(image, nullptr);
	EXPECT_EQ(image->GetPath(), path);
	EXPECT_EQ(image->GetWidth(), 10);
	EXPECT_EQ(image->GetHeight(), 10);

	command.TestDoUnexecute();

	EXPECT_EQ(image->GetPath(), path);
	EXPECT_EQ(image->GetWidth(), 800);
	EXPECT_EQ(image->GetHeight(), 900);
}

/*
class MockHistory : public History
{
public:
	MOCK_METHOD(bool, CanUndo, (), (const));
	MOCK_METHOD(bool, CanRedo, (), (const));
	MOCK_METHOD(void, Undo, (), ());
	MOCK_METHOD(void, Redo, (), ());
	MOCK_METHOD(void, AddAndExecuteCommand, (ICommandPtr && command), ());
};

class MockMenu : public IMenu
{
public:
	MOCK_METHOD(void, AddItem, (const std::string&, const std::string&, const Command&), (override));
	MOCK_METHOD(void, Run, (), (override));
	MOCK_METHOD(void, ShowInstructions, (), (const, override));
	MOCK_METHOD(void, Exit, (), (override));
	MOCK_METHOD(void, ExecuteCommand, (const std::string& command), (override));
};

class MockDocument : public IDocument
{
public:
	std::shared_ptr<IParagraph>
	InsertParagraph(const std::string& text, std::optional<size_t> position)
	{
		if (!position.has_value())
		{
			position = m_documentItems.size();
		}
		m_history.AddAndExecuteCommand(std::make_unique<InsertParagraphCommand>(m_documentItems, text, position));
		return m_documentItems.at(position.value()).GetParagraph();
	}

	void ReplaceText(const std::string& newText, std::optional<size_t> position)
	{
		m_history.AddAndExecuteCommand(std::make_unique<ReplaceTextCommand>(m_documentItems, newText, position));
	}

	void ResizeImage(int width, int height, std::optional<size_t> position)
	{
		m_history.AddAndExecuteCommand(std::make_unique<ResizeImageCommand>(m_documentItems, width, height, position));
	}

	std::shared_ptr<IImage>
	InsertImage(const std::string& path, int width, int height, std::optional<size_t> position)
	{
		m_history.AddAndExecuteCommand(std::make_unique<InsertImageCommand>(m_documentItems, path, width, height, position));
		if (position.has_value())
		{
			return m_documentItems.at(position.value()).GetImage();
		}
		else
		{
			return (--m_documentItems.end())->GetImage();
		}
	}

	size_t GetItemsCount() const
	{
		return m_documentItems.size();
	}

	ConstDocumentItem GetItem(size_t index) const
	{
		return m_documentItems.at(index);
	}

	DocumentItem GetItem(size_t index)
	{
		return m_documentItems.at(index);
	}

	void DeleteItem(size_t index)
	{
		m_history.AddAndExecuteCommand(std::make_unique<DeleteItemCommand>(m_documentItems, index));
	}

	std::string GetTitle() const
	{
		return m_title;
	}

	void SetTitle(const std::string& title)
	{
		m_history.AddAndExecuteCommand(std::make_unique<SetTitleCommand>(m_title, title));
	}

	bool CanUndo() const
	{
		return m_history.CanUndo();
	}

	void Undo()
	{
		m_history.Undo();
	}

	bool CanRedo() const
	{
		return m_history.CanRedo();
	}

	void Redo()
	{
		m_history.Redo();
	}

	void Save(const std::string& path) const
	{
		std::make_unique<SaveCommand>(m_documentItems, path, m_title)->Execute();
	}

	std::string m_title;
	MockHistory m_history;
	std::vector<DocumentItem> m_documentItems;
};

TEST(HistoryTest, HistoryUndoRedoTest)
{
	MockMenu* mockMenuPtr = new MockMenu();
	std::shared_ptr<IMenu> mockMenu(mockMenuPtr);

	CommandHandler commandHandler(mockMenu, std::make_unique<MockDocument>());
//	EXPECT_CALL(*mockMenuPtr, AddItem(testing::_, testing::_, testing::_)).WillRepeatedly();

}*/

GTEST_API_ int main(int argc, char** argv)
{
	std::cout << "Running tests" << std::endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}