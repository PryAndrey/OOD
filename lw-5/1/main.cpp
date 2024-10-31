#include "CommandHandler.h"
#include "models/document/Document.h"
#include <iostream>

int main(int argc, char* argv[])
{
	try
	{
		std::shared_ptr<IMenu> menu = std::make_shared<Menu>();
		CommandHandler commandHandler(menu, std::make_unique<Document>());

		menu->Run();
		menu->Exit();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
/*

todo replace съедает 1 слово - done
todo exit сделать а не по пустому вводу - done
todo Склеивание - done
todo Тесты
todo Копировать картинку во временный каталог

InsertParagraph end Hello bro1, I want to save long text
InsertParagraph end Hello bro2, I want to save long text
InsertParagraph end Hello bro3, I want to save long text
InsertImage 1 600 600 ../../1/example.jpg
SetTitle Hello file
ReplaceText 0 Hello bro(-1), I want to save long text
ResizeImage 1 900 1200
List
DeleteItem 3
List
Undo
Undo
List
Save C:\Users\ANDREY\Documents\GitHub\OOD\lw-5\1\result\result.html

InsertParagraph end Hello bro1, I want to save long text
InsertParagraph end Hello bro2, I want to save long text
InsertParagraph end Hello bro3, I want to save long text
ReplaceText 0 Hello bro(-1), I want to save long text
ReplaceText 0 Hello bro(-1), I want to save long text1


InsertParagraph end Hello bro1, I want to save long text
InsertParagraph end Hello bro2, I want to save long text
InsertParagraph end Hello bro3, I want to save long text
ReplaceText 0 Hello bro(-1), I want to save long text
ReplaceText 0 Hello bro(-1), I want to save long text1

Undo
InsertImage 0 600 600 ../../1/example.jpg
InsertImage 1 600 600 ../../1/example.jpg
ResizeImage 1 900 1200
ResizeImage 1 90 100
Undo
InsertParagraph end Hello bro1, I want to save long text
InsertParagraph end Hello bro2, I want to save long text
InsertParagraph end Hello bro3, I want to save long text
InsertParagraph end Hello bro1, I want to save long text
InsertParagraph end Hello bro2, I want to save long text
InsertParagraph end Hello bro3, I want to save long text
InsertParagraph end Hello bro1, I want to save long text
InsertParagraph end Hello bro2, I want to save long text
InsertParagraph end Hello bro3, I want to save long text
InsertParagraph end Hello bro1, I want to save long text
InsertParagraph end Hello bro2, I want to save long text
InsertParagraph end Hello bro3, I want to save long text
List

ReplaceText 10 Hello bro10
 */