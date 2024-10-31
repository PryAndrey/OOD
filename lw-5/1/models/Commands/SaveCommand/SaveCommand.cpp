#include "SaveCommand.h"

std::string SaveCommand::htmlTextEncode(const std::string& text)
{
	std::string encodedText;
	for (char c : text)
	{
		switch (c)
		{
		case '<':
			encodedText += "&lt;";
			break;
		case '>':
			encodedText += "&gt;";
			break;
		case '&':
			encodedText += "&amp;";
			break;
		default:
			encodedText += c;
			break;
		}
	}
	return encodedText;
}

std::string SaveCommand::htmlNameEncode(const std::string& text)
{
	std::string encodedName;
	for (char c : text)
	{
		switch (c)
		{
		case '"':
			encodedName += "&quot;";
			break;
		case '\'':
			encodedName += "&apos;";
			break;
		default:
			encodedName += c;
			break;
		}
	}
	return encodedName;
}

void SaveCommand::DoExecute()
{
	std::ofstream outFile(m_path);
	if (!outFile.is_open())
	{
		throw std::runtime_error("Can`t open file for writing");
	}
	std::filesystem::path basePath = std::filesystem::path(m_path).parent_path();
	std::filesystem::path imagesDir = basePath / "images";

	outFile << "<!DOCTYPE html>" << std::endl
			<< "<html>" << std::endl
			<< "<head>" << std::endl;
	outFile << "<title>" << htmlTextEncode(m_title) << "</title>" << std::endl;
	outFile << "</head>" << std::endl
			<< "<body>" << std::endl;

	int imgInd = 1;
	for (const ConstDocumentItem& item : m_documentItems)
	{
		auto paragraph = item.GetParagraph();
		if (paragraph != nullptr)
		{
			outFile << "<p>" << htmlTextEncode(paragraph->GetText()) << "</p>" << std::endl;
		}
		auto image = item.GetImage();
		if (image != nullptr)
		{
			if (!std::filesystem::exists(imagesDir))
			{
				std::filesystem::create_directory(imagesDir);
			}
			std::string imagePath = image->GetPath();
			std::string imageFileName = "Img" + std::to_string(imgInd++) + "." + imagePath.substr(imagePath.find_last_of('.') + 1);
			std::string destinationPath = (imagesDir / imageFileName).string();
			if (std::filesystem::exists(destinationPath))
			{
				std::filesystem::remove(destinationPath);
			}
			std::filesystem::copy(imagePath, destinationPath, std::filesystem::copy_options::overwrite_existing);

			outFile << "<img src=\"" << ("images/" + htmlNameEncode(htmlTextEncode(imageFileName))) << "\" "
					<< "width=\"" << image->GetWidth() << "\" "
					<< "height=\"" << image->GetHeight() << "\" "
					<< "alt=\"Image\" />" << std::endl;
		}
	}
	outFile << "</body>" << std::endl
			<< "</html>";
	outFile.close();
}

void SaveCommand::DoUnexecute()
{
}

std::string SaveCommand::GetParamsForGlue()
{
}

bool SaveCommand::IsGlueAble() const
{
	return false;
}